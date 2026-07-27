/*
 * Focused OSMesa vertex-shader interpreter benchmark.
 *
 * The points are deliberately outside the clip volume so rasterization does
 * not obscure the cost of vertex transformation.  The fixed, pass-through
 * GLSL, and arithmetic-heavy GLSL modes consume the same VBO.
 *
 * This program is in the public domain.
 */

#define GL_GLEXT_PROTOTYPES
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#  include <windows.h>
#else
#  include <sys/time.h>
#endif

#include "OSMesa/gl.h"
#include "OSMesa/glext.h"
#include "OSMesa/osmesa.h"

#define MAX_COUNT (1L << 30)

static const char *pass_vertex_shader =
    "#version 110\n"
    "void main() {\n"
    "    gl_Position = gl_Vertex;\n"
    "}\n";

static const char *pop_vertex_shader =
    "#version 110\n"
    "uniform mat4 transform;\n"
    "uniform vec3 origin;\n"
    "uniform float cell;\n"
    "void main() {\n"
    "    vec3 p = floor((gl_Vertex.xyz - origin) / cell + vec3(0.5));\n"
    "    p = p * cell + origin;\n"
    "    gl_Position = transform * vec4(p, 1.0);\n"
    "}\n";

/* Keep this algorithm in sync with Obol's Tier-1 CAD wire/shaded shaders.
 * Unlike the arithmetic-only "pop" kernel, it exercises slang's generated
 * comparisons, condition codes, subroutine call, and early return.
 */
static const char *obol_pop_vertex_shader =
    "#version 110\n"
    "uniform mat4 u_model;\n"
    "uniform mat4 u_viewProj;\n"
    "uniform int u_popLevel;\n"
    "uniform float u_popMask;\n"
    "uniform vec3 u_popMin;\n"
    "uniform vec3 u_popMax;\n"
    "vec3 popPosition(vec3 p) {\n"
    "    if (u_popLevel < 0 || u_popLevel >= 15) return p;\n"
    "    vec3 extent = u_popMax - u_popMin;\n"
    "    vec3 safeExtent = max(extent, vec3(1.0e-30));\n"
    "    vec3 scaled = (p - u_popMin) / safeExtent * 65535.0;\n"
    "    vec3 low = floor(floor(scaled) / u_popMask);\n"
    "    vec3 high = ceil(ceil(scaled) / u_popMask);\n"
    "    return ((low + high) * (0.5 * u_popMask / 65535.0)) *\n"
    "           extent + u_popMin;\n"
    "}\n"
    "void main() {\n"
    "    vec4 wp = u_model * vec4(popPosition(gl_Vertex.xyz), 1.0);\n"
    "    gl_Position = u_viewProj * wp;\n"
    "}\n";

/* The same snap rule with per-draw invariant work supplied as uniforms and
 * the exact/PoP choice made before selecting the shader program.
 */
static const char *obol_pop_optimized_vertex_shader =
    "#version 110\n"
    "uniform mat4 u_model;\n"
    "uniform mat4 u_viewProj;\n"
    "uniform vec3 u_popEncodeScale;\n"
    "uniform vec3 u_popDecodeScale;\n"
    "uniform vec3 u_popMin;\n"
    "void main() {\n"
    "    vec3 scaled = (gl_Vertex.xyz - u_popMin) * u_popEncodeScale;\n"
    "    vec3 low = floor(scaled);\n"
    "    vec3 high = ceil(scaled);\n"
    "    vec3 p = (low + high) * u_popDecodeScale + u_popMin;\n"
    "    vec4 wp = u_model * vec4(p, 1.0);\n"
    "    gl_Position = u_viewProj * wp;\n"
    "}\n";

static const char *fragment_shader =
    "#version 110\n"
    "void main() {\n"
    "    gl_FragColor = vec4(1.0);\n"
    "}\n";

static double
now_seconds(void)
{
#ifdef _WIN32
    LARGE_INTEGER counter;
    LARGE_INTEGER frequency;
    QueryPerformanceCounter(&counter);
    QueryPerformanceFrequency(&frequency);
    return (double) counter.QuadPart / (double) frequency.QuadPart;
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
#endif
}

static int
parse_positive(const char *name, const char *value, GLint *result)
{
    char *end = NULL;
    long parsed = strtol(value, &end, 10);

    if (!value[0] || *end || parsed <= 0 || parsed > MAX_COUNT) {
	fprintf(stderr, "invalid value for %s: %s\n", name, value);
	return 0;
    }
    *result = (GLint) parsed;
    return 1;
}

static GLuint
compile_shader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    GLint ok = GL_FALSE;

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
	GLchar log[1024];
	glGetShaderInfoLog(shader, sizeof(log), NULL, log);
	fprintf(stderr, "%s shader compilation failed: %s\n",
		type == GL_VERTEX_SHADER ? "vertex" : "fragment", log);
	glDeleteShader(shader);
	return 0;
    }
    return shader;
}

static GLuint
make_program(const char *vertex_source)
{
    GLuint vertex = compile_shader(GL_VERTEX_SHADER, vertex_source);
    GLuint fragment;
    GLuint program;
    GLint ok = GL_FALSE;

    if (!vertex)
	return 0;
    fragment = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);
    if (!fragment) {
	glDeleteShader(vertex);
	return 0;
    }

    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &ok);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (!ok) {
	GLchar log[1024];
	glGetProgramInfoLog(program, sizeof(log), NULL, log);
	fprintf(stderr, "program link failed: %s\n", log);
	glDeleteProgram(program);
	return 0;
    }
    return program;
}

static int
prepare_pop_program(GLuint program)
{
    static const GLfloat identity[16] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
    };
    GLint transform = glGetUniformLocation(program, "transform");
    GLint origin = glGetUniformLocation(program, "origin");
    GLint cell = glGetUniformLocation(program, "cell");

    if (transform < 0 || origin < 0 || cell < 0) {
	fprintf(stderr, "PoP benchmark uniforms were optimized away\n");
	return 0;
    }
    glUniformMatrix4fv(transform, 1, GL_FALSE, identity);
    glUniform3f(origin, 0.125f, -0.25f, 0.375f);
    glUniform1f(cell, 0.03125f);
    return 1;
}

static int
prepare_obol_pop_program(GLuint program)
{
    static const GLfloat identity[16] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
    };
    GLint model = glGetUniformLocation(program, "u_model");
    GLint view_projection = glGetUniformLocation(program, "u_viewProj");
    GLint level = glGetUniformLocation(program, "u_popLevel");
    GLint mask = glGetUniformLocation(program, "u_popMask");
    GLint minimum = glGetUniformLocation(program, "u_popMin");
    GLint maximum = glGetUniformLocation(program, "u_popMax");

    if (model < 0 || view_projection < 0 || level < 0 || mask < 0 ||
	minimum < 0 || maximum < 0) {
	fprintf(stderr, "Obol PoP benchmark uniforms were optimized away\n");
	return 0;
    }
    glUniformMatrix4fv(model, 1, GL_FALSE, identity);
    glUniformMatrix4fv(view_projection, 1, GL_FALSE, identity);
    glUniform1i(level, 9);
    glUniform1f(mask, 64.0f);
    glUniform3f(minimum, -2.0f, -2.0f, -2.0f);
    glUniform3f(maximum, 2.5f, 2.5f, 2.5f);
    return 1;
}

static int
prepare_obol_pop_optimized_program(GLuint program)
{
    static const GLfloat identity[16] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
    };
    GLint model = glGetUniformLocation(program, "u_model");
    GLint view_projection = glGetUniformLocation(program, "u_viewProj");
    GLint encode = glGetUniformLocation(program, "u_popEncodeScale");
    GLint decode = glGetUniformLocation(program, "u_popDecodeScale");
    GLint minimum = glGetUniformLocation(program, "u_popMin");
    const GLfloat extent = 4.5f;
    const GLfloat mask = 64.0f;

    if (model < 0 || view_projection < 0 || encode < 0 || decode < 0 ||
	minimum < 0) {
	fprintf(stderr, "optimized Obol PoP benchmark uniforms were optimized away\n");
	return 0;
    }
    glUniformMatrix4fv(model, 1, GL_FALSE, identity);
    glUniformMatrix4fv(view_projection, 1, GL_FALSE, identity);
    glUniform3f(encode, 65535.0f / (extent * mask),
		65535.0f / (extent * mask),
		65535.0f / (extent * mask));
    glUniform3f(decode, 0.5f * mask * extent / 65535.0f,
		0.5f * mask * extent / 65535.0f,
		0.5f * mask * extent / 65535.0f);
    glUniform3f(minimum, -2.0f, -2.0f, -2.0f);
    return 1;
}

static int
run_mode(const char *name, GLuint program, GLint vertices, GLint warmup,
	 GLint frames)
{
    GLint frame;
    double start;
    double elapsed;
    double total_vertices;

    glUseProgram(program);
    if (program && strcmp(name, "pop") == 0 && !prepare_pop_program(program))
	return 0;
    if (program && strcmp(name, "obol-pop") == 0 &&
	!prepare_obol_pop_program(program))
	return 0;
    if (program && strcmp(name, "obol-pop-opt") == 0 &&
	!prepare_obol_pop_optimized_program(program))
	return 0;

    for (frame = 0; frame < warmup; frame++) {
	glDrawArrays(GL_POINTS, 0, vertices);
	glFinish();
    }

    start = now_seconds();
    for (frame = 0; frame < frames; frame++) {
	glDrawArrays(GL_POINTS, 0, vertices);
	glFinish();
    }
    elapsed = now_seconds() - start;
    total_vertices = (double) vertices * (double) frames;

    if (glGetError() != GL_NO_ERROR) {
	fprintf(stderr, "%s mode generated an OpenGL error\n", name);
	return 0;
    }

    printf("mode=%-11s vertices=%d frames=%d elapsed=%.6f "
	   "Mvertices_per_sec=%.3f ns_per_vertex=%.2f\n",
	   name, vertices, frames, elapsed,
	   total_vertices / elapsed / 1000000.0,
	   elapsed * 1000000000.0 / total_vertices);
    return 1;
}

int
main(int argc, char **argv)
{
    const char *mode = "all";
    GLint vertices = 262144;
    GLint frames = 10;
    GLint warmup = 2;
    GLfloat *positions;
    GLubyte framebuffer[4 * 4 * 4] = {0};
    OSMesaContext context;
    GLuint buffer = 0;
    GLuint pass_program = 0;
    GLuint pop_program = 0;
    GLuint obol_pop_program = 0;
    GLuint obol_pop_optimized_program = 0;
    GLint i;
    int ok = 1;

    for (i = 1; i < argc; i++) {
	if (strcmp(argv[i], "--vertices") == 0 && i + 1 < argc) {
	    if (!parse_positive("--vertices", argv[++i], &vertices))
		return 1;
	} else if (strcmp(argv[i], "--frames") == 0 && i + 1 < argc) {
	    if (!parse_positive("--frames", argv[++i], &frames))
		return 1;
	} else if (strcmp(argv[i], "--warmup") == 0 && i + 1 < argc) {
	    if (!parse_positive("--warmup", argv[++i], &warmup))
		return 1;
	} else if (strcmp(argv[i], "--mode") == 0 && i + 1 < argc) {
	    mode = argv[++i];
	} else if (strcmp(argv[i], "--help") == 0) {
	    printf("usage: %s [--mode all|fixed|pass|pop|obol-pop|obol-pop-opt] [--vertices N] "
		   "[--frames N] [--warmup N]\n", argv[0]);
	    return 0;
	} else {
	    fprintf(stderr, "unknown argument: %s\n", argv[i]);
	    return 1;
	}
    }

    if (strcmp(mode, "all") != 0 && strcmp(mode, "fixed") != 0 &&
	strcmp(mode, "pass") != 0 && strcmp(mode, "pop") != 0 &&
	strcmp(mode, "obol-pop") != 0 && strcmp(mode, "obol-pop-opt") != 0) {
	fprintf(stderr,
		"mode must be all, fixed, pass, pop, obol-pop, or obol-pop-opt\n");
	return 1;
    }
    if ((size_t) vertices > SIZE_MAX / (4 * sizeof(GLfloat))) {
	fprintf(stderr, "vertex allocation size overflow\n");
	return 1;
    }

    positions = (GLfloat *) malloc((size_t) vertices * 4 * sizeof(GLfloat));
    if (!positions) {
	fprintf(stderr, "vertex allocation failed\n");
	return 1;
    }
    for (i = 0; i < vertices; i++) {
	positions[4 * i + 0] = 2.0f + (GLfloat)(i & 15) * 0.001f;
	positions[4 * i + 1] = 2.0f + (GLfloat)((i >> 4) & 15) * 0.001f;
	positions[4 * i + 2] = 0.0f;
	positions[4 * i + 3] = 1.0f;
    }

    context = OSMesaCreateContextExt(OSMESA_RGBA, 0, 0, 0, NULL);
    if (!context ||
	!OSMesaMakeCurrent(context, framebuffer, GL_UNSIGNED_BYTE, 4, 4)) {
	fprintf(stderr, "OSMesa context creation failed\n");
	free(positions);
	if (context)
	    OSMesaDestroyContext(context);
	return 1;
    }

    printf("renderer=%s version=%s\n", glGetString(GL_RENDERER),
	   glGetString(GL_VERSION));
    glViewport(0, 0, 4, 4);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_DITHER);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER,
		 (GLsizeiptr) ((size_t) vertices * 4 * sizeof(GLfloat)),
		 positions, GL_STATIC_DRAW);
    free(positions);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(4, GL_FLOAT, 0, (const GLvoid *) 0);

    pass_program = make_program(pass_vertex_shader);
    pop_program = make_program(pop_vertex_shader);
    obol_pop_program = make_program(obol_pop_vertex_shader);
    obol_pop_optimized_program =
	make_program(obol_pop_optimized_vertex_shader);
    if (!pass_program || !pop_program || !obol_pop_program ||
	!obol_pop_optimized_program) {
	ok = 0;
	goto cleanup;
    }

    if ((strcmp(mode, "all") == 0 || strcmp(mode, "fixed") == 0) &&
	!run_mode("fixed", 0, vertices, warmup, frames))
	ok = 0;
    if ((strcmp(mode, "all") == 0 || strcmp(mode, "pass") == 0) &&
	!run_mode("pass", pass_program, vertices, warmup, frames))
	ok = 0;
    if ((strcmp(mode, "all") == 0 || strcmp(mode, "pop") == 0) &&
	!run_mode("pop", pop_program, vertices, warmup, frames))
	ok = 0;
    if ((strcmp(mode, "all") == 0 || strcmp(mode, "obol-pop") == 0) &&
	!run_mode("obol-pop", obol_pop_program, vertices, warmup, frames))
	ok = 0;
    if ((strcmp(mode, "all") == 0 ||
	 strcmp(mode, "obol-pop-opt") == 0) &&
	!run_mode("obol-pop-opt", obol_pop_optimized_program, vertices,
		  warmup, frames))
	ok = 0;

cleanup:
    glUseProgram(0);
    glDisableClientState(GL_VERTEX_ARRAY);
    if (buffer)
	glDeleteBuffers(1, &buffer);
    if (pass_program)
	glDeleteProgram(pass_program);
    if (pop_program)
	glDeleteProgram(pop_program);
    if (obol_pop_program)
	glDeleteProgram(obol_pop_program);
    if (obol_pop_optimized_program)
	glDeleteProgram(obol_pop_optimized_program);
    OSMesaDestroyContext(context);
    return ok ? 0 : 1;
}
