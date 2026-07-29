/*
 * Focused OSMesa fragment-shader benchmark.
 *
 * A pair of triangles covers the viewport.  The GLSL shaders mirror Obol's
 * common one-directional-light CAD programs, including the derivative-normal
 * path used by PoP meshes without authored normals.  Fixed-function lighting
 * provides the compatibility-path baseline.
 *
 * This program is in the public domain.
 */

#define GL_GLEXT_PROTOTYPES
#include <inttypes.h>
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

#define MAX_DIMENSION 16384L
#define MAX_COUNT (1L << 30)

static const char *cad_vertex_shader =
    "#version 110\n"
    "attribute vec3 a_pos;\n"
    "attribute vec3 a_norm;\n"
    "uniform vec4 u_color;\n"
    "varying vec3 v_norm;\n"
    "varying vec3 v_worldPos;\n"
    "varying vec4 v_color;\n"
    "void main() {\n"
    "    gl_Position = vec4(a_pos, 1.0);\n"
    "    v_worldPos = a_pos;\n"
    "    v_norm = a_norm;\n"
    "    v_color = u_color;\n"
    "}\n";

static const char *pass_fragment_shader =
    "#version 110\n"
    "varying vec4 v_color;\n"
    "void main() { gl_FragColor = v_color; }\n";

static const char *normal_fragment_shader =
    "#version 110\n"
    "uniform vec3 u_lightVec;\n"
    "uniform vec3 u_lightColor;\n"
    "varying vec3 v_norm;\n"
    "varying vec4 v_color;\n"
    "void main() {\n"
    "    vec3 n = normalize(v_norm);\n"
    "    n *= gl_FrontFacing ? 1.0 : -1.0;\n"
    "    float ndl = max(0.0, dot(n, u_lightVec));\n"
    "    float spec = (ndl > 0.0) ? 0.2 : 0.0;\n"
    "    vec3 col = v_color.rgb *\n"
    "        (vec3(0.06) + u_lightColor * (ndl * 0.6 + spec));\n"
    "    gl_FragColor = vec4(col, v_color.a);\n"
    "}\n";

static const char *face_fragment_shader =
    "#version 110\n"
    "uniform vec3 u_lightVec;\n"
    "uniform vec3 u_lightColor;\n"
    "uniform vec3 u_viewTowardEye;\n"
    "varying vec3 v_worldPos;\n"
    "varying vec4 v_color;\n"
    "void main() {\n"
    "    vec3 fn = cross(dFdx(v_worldPos), dFdy(v_worldPos));\n"
    "    vec3 n = fn * inversesqrt(max(dot(fn, fn), 1.0e-30));\n"
    "    n *= 2.0 * step(0.0, dot(n, u_viewTowardEye)) - 1.0;\n"
    "    float ndl = max(0.0, dot(n, u_lightVec));\n"
    "    float spec = (ndl > 0.0) ? 0.2 : 0.0;\n"
    "    vec3 col = v_color.rgb *\n"
    "        (vec3(0.06) + u_lightColor * (ndl * 0.6 + spec));\n"
    "    gl_FragColor = vec4(col, v_color.a);\n"
    "}\n";

static double
now_seconds(void)
{
#ifdef _WIN32
    LARGE_INTEGER counter;
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);
    return (double) counter.QuadPart / (double) frequency.QuadPart;
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
#endif
}

static uint64_t
framebuffer_hash(const GLubyte *data, size_t size)
{
    uint64_t hash = UINT64_C(1469598103934665603);
    size_t i;
    for (i = 0; i < size; ++i) {
	hash ^= data[i];
	hash *= UINT64_C(1099511628211);
    }
    return hash;
}

static int
parse_positive(const char *name, const char *value, GLint maximum,
	       GLint *result)
{
    char *end = NULL;
    long parsed = strtol(value, &end, 10);
    if (!value[0] || *end || parsed <= 0 || parsed > maximum) {
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
	GLchar log[2048];
	glGetShaderInfoLog(shader, sizeof(log), NULL, log);
	fprintf(stderr, "%s shader compilation failed: %s\n",
		type == GL_VERTEX_SHADER ? "vertex" : "fragment", log);
	glDeleteShader(shader);
	return 0;
    }
    return shader;
}

static GLuint
make_program(const char *fragment_source)
{
    GLuint vertex = compile_shader(GL_VERTEX_SHADER, cad_vertex_shader);
    GLuint fragment = compile_shader(GL_FRAGMENT_SHADER, fragment_source);
    GLuint program;
    GLint ok = GL_FALSE;
    if (!vertex || !fragment) {
	if (vertex) glDeleteShader(vertex);
	if (fragment) glDeleteShader(fragment);
	return 0;
    }
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glBindAttribLocation(program, 0, "a_pos");
    glBindAttribLocation(program, 1, "a_norm");
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &ok);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (!ok) {
	GLchar log[2048];
	glGetProgramInfoLog(program, sizeof(log), NULL, log);
	fprintf(stderr, "program link failed: %s\n", log);
	glDeleteProgram(program);
	return 0;
    }
    return program;
}

static int
prepare_program(GLuint program)
{
    const GLfloat color[4] = {0.8f, 0.25f, 0.1f, 1.0f};
    const GLfloat light[3] = {0.0f, 0.0f, 1.0f};
    GLint location;
    glUseProgram(program);
    location = glGetUniformLocation(program, "u_color");
    if (location >= 0) glUniform4fv(location, 1, color);
    location = glGetUniformLocation(program, "u_lightVec");
    if (location >= 0) glUniform3fv(location, 1, light);
    location = glGetUniformLocation(program, "u_lightColor");
    if (location >= 0) glUniform3fv(location, 1, light);
    location = glGetUniformLocation(program, "u_viewTowardEye");
    if (location >= 0) glUniform3fv(location, 1, light);
    return glGetError() == GL_NO_ERROR;
}

static void
prepare_fixed(void)
{
    const GLfloat global_ambient[4] = {0.3f, 0.3f, 0.3f, 1.0f};
    const GLfloat light_position[4] = {0.0f, 0.0f, 1.0f, 0.0f};
    const GLfloat light_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    const GLfloat material_ambient[4] = {0.16f, 0.05f, 0.02f, 1.0f};
    const GLfloat material_diffuse[4] = {0.48f, 0.15f, 0.06f, 1.0f};
    const GLfloat material_specular[4] = {0.16f, 0.05f, 0.02f, 1.0f};
    const GLfloat zero[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    glUseProgram(0);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, zero);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, zero);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
}

static int
run_mode(const char *name, GLuint program, GLint width, GLint height,
	 GLint warmup, GLint frames, const GLubyte *framebuffer,
	 size_t framebuffer_size)
{
    GLint frame;
    double start;
    double elapsed;
    const double pixels = (double) width * (double) height * frames;
    if (strcmp(name, "fixed") == 0)
	prepare_fixed();
    else {
	glDisable(GL_LIGHTING);
	if (!prepare_program(program)) return 0;
    }
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    for (frame = 0; frame < warmup; ++frame) {
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glFinish();
    }
    start = now_seconds();
    for (frame = 0; frame < frames; ++frame) {
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glFinish();
    }
    elapsed = now_seconds() - start;
    if (glGetError() != GL_NO_ERROR) {
	fprintf(stderr, "%s mode generated an OpenGL error\n", name);
	return 0;
    }
    printf("mode=%-6s size=%dx%d frames=%d elapsed=%.6f "
	   "Mpixels_per_sec=%.3f ns_per_pixel=%.2f hash=%016" PRIx64 "\n",
	   name, width, height, frames, elapsed,
	   pixels / elapsed / 1000000.0,
	   elapsed * 1000000000.0 / pixels,
	   framebuffer_hash(framebuffer, framebuffer_size));
    return 1;
}

int
main(int argc, char **argv)
{
    static const GLfloat vertices[6][6] = {
	{-1, -1, 0, 0, 0, 1}, { 1, -1, 0, 0, 0, 1},
	{ 1,  1, 0, 0, 0, 1}, {-1, -1, 0, 0, 0, 1},
	{ 1,  1, 0, 0, 0, 1}, {-1,  1, 0, 0, 0, 1}
    };
    const char *mode = "all";
    GLint width = 1024, height = 768, frames = 20, warmup = 4;
    size_t framebuffer_size;
    GLubyte *framebuffer = NULL;
    OSMesaContext context = NULL;
    GLuint buffer = 0, pass_program = 0, normal_program = 0, face_program = 0;
    GLint i;
    int ok = 1;
    for (i = 1; i < argc; ++i) {
	if (strcmp(argv[i], "--width") == 0 && i + 1 < argc) {
	    if (!parse_positive("--width", argv[++i], MAX_DIMENSION, &width))
		return 1;
	} else if (strcmp(argv[i], "--height") == 0 && i + 1 < argc) {
	    if (!parse_positive("--height", argv[++i], MAX_DIMENSION, &height))
		return 1;
	} else if (strcmp(argv[i], "--frames") == 0 && i + 1 < argc) {
	    if (!parse_positive("--frames", argv[++i], MAX_COUNT, &frames))
		return 1;
	} else if (strcmp(argv[i], "--warmup") == 0 && i + 1 < argc) {
	    if (!parse_positive("--warmup", argv[++i], MAX_COUNT, &warmup))
		return 1;
	} else if (strcmp(argv[i], "--mode") == 0 && i + 1 < argc) {
	    mode = argv[++i];
	} else if (strcmp(argv[i], "--help") == 0) {
	    printf("usage: %s [--mode all|fixed|pass|normal|face] "
		   "[--width N] [--height N] [--frames N] [--warmup N]\n",
		   argv[0]);
	    return 0;
	} else {
	    fprintf(stderr, "unknown argument: %s\n", argv[i]);
	    return 1;
	}
    }
    if (strcmp(mode, "all") != 0 && strcmp(mode, "fixed") != 0 &&
	strcmp(mode, "pass") != 0 && strcmp(mode, "normal") != 0 &&
	strcmp(mode, "face") != 0) {
	fprintf(stderr, "mode must be all, fixed, pass, normal, or face\n");
	return 1;
    }
    if ((size_t) width > SIZE_MAX / 4 / (size_t) height) {
	fprintf(stderr, "framebuffer allocation size overflow\n");
	return 1;
    }
    framebuffer_size = (size_t) width * (size_t) height * 4;
    framebuffer = (GLubyte *) calloc(1, framebuffer_size);
    context = OSMesaCreateContextExt(OSMESA_RGBA, 0, 0, 0, NULL);
    if (!framebuffer || !context ||
	!OSMesaMakeCurrent(context, framebuffer, GL_UNSIGNED_BYTE, width, height)) {
	fprintf(stderr, "OSMesa setup failed\n");
	ok = 0;
	goto cleanup;
    }
    printf("renderer=%s version=%s\n", glGetString(GL_RENDERER),
	   glGetString(GL_VERSION));
    glViewport(0, 0, width, height);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_DITHER);
    glDisable(GL_CULL_FACE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), (const GLvoid *) 0);
    glNormalPointer(GL_FLOAT, 6 * sizeof(GLfloat),
		    (const GLvoid *) (uintptr_t) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
			  (const GLvoid *) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
			  (const GLvoid *) (uintptr_t) (3 * sizeof(GLfloat)));
    pass_program = make_program(pass_fragment_shader);
    normal_program = make_program(normal_fragment_shader);
    face_program = make_program(face_fragment_shader);
    if (!pass_program || !normal_program || !face_program) {
	ok = 0;
	goto cleanup;
    }
    if ((strcmp(mode, "all") == 0 || strcmp(mode, "fixed") == 0) &&
	!run_mode("fixed", 0, width, height, warmup, frames,
		  framebuffer, framebuffer_size)) ok = 0;
    if ((strcmp(mode, "all") == 0 || strcmp(mode, "pass") == 0) &&
	!run_mode("pass", pass_program, width, height, warmup, frames,
		  framebuffer, framebuffer_size)) ok = 0;
    if ((strcmp(mode, "all") == 0 || strcmp(mode, "normal") == 0) &&
	!run_mode("normal", normal_program, width, height, warmup, frames,
		  framebuffer, framebuffer_size)) ok = 0;
    if ((strcmp(mode, "all") == 0 || strcmp(mode, "face") == 0) &&
	!run_mode("face", face_program, width, height, warmup, frames,
		  framebuffer, framebuffer_size)) ok = 0;

cleanup:
    glUseProgram(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    if (buffer) glDeleteBuffers(1, &buffer);
    if (pass_program) glDeleteProgram(pass_program);
    if (normal_program) glDeleteProgram(normal_program);
    if (face_program) glDeleteProgram(face_program);
    if (context) OSMesaDestroyContext(context);
    free(framebuffer);
    return ok ? 0 : 1;
}
