/*
 * OpenGL 2.0 / extension stress test for OSMesa.
 *
 * Tests the extensions listed in the problem statement that OSMesa
 * claims to support, exercising them as they are intended to be used.
 *
 * Extensions tested:
 *   GL_EXT_polygon_offset
 *   GL_EXT_texture_object
 *   GL_EXT_subtexture
 *   GL_EXT_texture3D
 *   GL_ARB_multitexture
 *   GL_ARB_texture_compression
 *   GL_EXT_paletted_texture
 *   GL_ARB_imaging  (includes GL_EXT_blend_minmax, GL_SGI_color_matrix,
 *                    GL_SGI_color_table, GL_SGI_texture_color_table)
 *   GL_EXT_blend_minmax
 *   GL_SGI_color_table
 *   GL_SGI_texture_color_table
 *   GL_ARB_vertex_buffer_object
 *   GL_EXT_multi_draw_arrays
 *   GL_ARB_depth_texture
 *   GL_ARB_shadow
 *   GL_EXT_texture_rectangle
 *   GL_ARB_fragment_program
 *   GL_ARB_vertex_program
 *   GL_ARB_shader_objects
 *   GL_ARB_vertex_shader
 *   GL_ARB_occlusion_query
 *
 * This program is in the public domain.
 */

#define _USE_MATH_DEFINES
#define GL_GLEXT_PROTOTYPES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "OSMesa/gl.h"
#include "OSMesa/glext.h"
#include "OSMesa/osmesa.h"

/* ------------------------------------------------------------------ */
/* Helpers                                                             */
/* ------------------------------------------------------------------ */

static int g_failed = 0;

static int
check_ext(const char *name)
{
    const char *exts = (const char *)glGetString(GL_EXTENSIONS);
    if (!exts || !strstr(exts, name)) {
	fprintf(stderr, "  SKIP: %s not advertised\n", name);
	return 0;
    }
    return 1;
}

static int
check_gl_error(const char *where)
{
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
	fprintf(stderr, "  GL error 0x%x at %s\n", (unsigned)err, where);
	return 1;
    }
    return 0;
}

static void
clear_errors(void)
{
    while (glGetError() != GL_NO_ERROR)
	;
}

/* Draw a full-screen quad */
static void
draw_quad(void)
{
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f( 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f( 1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f,  1.0f);
    glEnd();
}

/* Compile+link a simple GLSL program */
static GLuint
make_program(const char *vert_src, const char *frag_src)
{
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vert_src, NULL);
    glCompileShader(vert);
    GLint ok = 0;
    glGetShaderiv(vert, GL_COMPILE_STATUS, &ok);
    if (!ok) {
	char log[512];
	glGetShaderInfoLog(vert, sizeof(log), NULL, log);
	fprintf(stderr, "  Vert shader error: %s\n", log);
	glDeleteShader(vert);
	return 0;
    }

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &frag_src, NULL);
    glCompileShader(frag);
    glGetShaderiv(frag, GL_COMPILE_STATUS, &ok);
    if (!ok) {
	char log[512];
	glGetShaderInfoLog(frag, sizeof(log), NULL, log);
	fprintf(stderr, "  Frag shader error: %s\n", log);
	glDeleteShader(vert);
	glDeleteShader(frag);
	return 0;
    }

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    glDeleteShader(vert);
    glDeleteShader(frag);
    if (!ok) {
	char log[512];
	glGetProgramInfoLog(prog, sizeof(log), NULL, log);
	fprintf(stderr, "  Program link error: %s\n", log);
	glDeleteProgram(prog);
	return 0;
    }
    return prog;
}

/* ------------------------------------------------------------------ */
/* Test 1: Extension advertisement                                     */
/* ------------------------------------------------------------------ */
static void
test_extension_strings(void)
{
    printf("Test 1: Extension advertisement\n");

    /* Extensions from the problem statement that OSMesa claims to support */
    static const char * const supported[] = {
	"GL_EXT_polygon_offset",
	"GL_EXT_texture_object",
	"GL_EXT_subtexture",
	"GL_EXT_texture3D",
	"GL_ARB_multitexture",
	"GL_ARB_texture_compression",
	"GL_EXT_paletted_texture",
	"GL_ARB_imaging",
	"GL_EXT_blend_minmax",
	"GL_SGI_color_table",
	"GL_SGI_texture_color_table",
	"GL_ARB_vertex_buffer_object",
	"GL_EXT_multi_draw_arrays",
	"GL_ARB_depth_texture",
	"GL_EXT_framebuffer_object",
	"GL_ARB_shadow",
	"GL_EXT_texture_rectangle",
	"GL_ARB_fragment_program",
	"GL_ARB_vertex_program",
	"GL_ARB_shader_objects",
	"GL_ARB_vertex_shader",
	"GL_ARB_occlusion_query",
	NULL
    };

    const char *exts = (const char *)glGetString(GL_EXTENSIONS);
    if (!exts) {
	fprintf(stderr, "  FAIL: glGetString(GL_EXTENSIONS) returned NULL\n");
	g_failed++;
	return;
    }

    int all_ok = 1;
    for (int i = 0; supported[i]; i++) {
	if (!strstr(exts, supported[i])) {
	    fprintf(stderr, "  FAIL: %s not advertised\n", supported[i]);
	    all_ok = 0;
	    g_failed++;
	}
    }
    if (all_ok)
	printf("  PASS: all expected extensions advertised\n");
}

/* ------------------------------------------------------------------ */
/* Test 2: GL_EXT_polygon_offset                                       */
/* ------------------------------------------------------------------ */
static void
test_polygon_offset(int W, int H)
{
    printf("Test 2: GL_EXT_polygon_offset\n");

    if (!check_ext("GL_EXT_polygon_offset"))
	return;

    clear_errors();

    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0, 1.0);

    /* Draw a base polygon and read its depth */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f( 0.5f, -0.5f, 0.0f);
    glVertex3f( 0.5f,  0.5f, 0.0f);
    glVertex3f(-0.5f,  0.5f, 0.0f);
    glEnd();
    glFinish();

    GLfloat depth_base = 0.0f;
    glReadPixels(W/2, H/2, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth_base);

    /* Draw the same polygon with a positive offset */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f( 0.5f, -0.5f, 0.0f);
    glVertex3f( 0.5f,  0.5f, 0.0f);
    glVertex3f(-0.5f,  0.5f, 0.0f);
    glEnd();
    glFinish();

    GLfloat depth_offset = 0.0f;
    glReadPixels(W/2, H/2, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth_offset);

    glDisable(GL_POLYGON_OFFSET_FILL);
    glDisable(GL_DEPTH_TEST);

    if (check_gl_error("polygon_offset")) {
	fprintf(stderr, "  FAIL: GL error during polygon offset test\n");
	g_failed++;
	return;
    }

    /* With positive offset, depth should be pushed farther (larger value) */
    if (depth_offset > depth_base) {
	printf("  PASS: polygon offset increases depth (%.4f -> %.4f)\n",
	       depth_base, depth_offset);
    } else {
	fprintf(stderr,
		"  FAIL: polygon offset did not increase depth "
		"(base=%.4f, offset=%.4f)\n",
		depth_base, depth_offset);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 3: GL_EXT_texture_object                                       */
/* ------------------------------------------------------------------ */
static void
test_texture_object(int W, int H)
{
    printf("Test 3: GL_EXT_texture_object\n");

    if (!check_ext("GL_EXT_texture_object"))
	return;

    clear_errors();

    /* Create two textures - one red, one green */
    GLuint textures[2];
    glGenTextures(2, textures);

    GLubyte red[4]   = { 255, 0, 0, 255 };
    GLubyte green[4] = { 0, 255, 0, 255 };

    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, red);

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, green);

    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    /* Render with the red texture */
    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    draw_quad();
    glFinish();

    GLubyte px[4] = {0};
    glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);

    int red_ok = (px[0] > 200 && px[1] < 50 && px[2] < 50);

    /* Render with the green texture */
    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    draw_quad();
    glFinish();

    GLubyte px2[4] = {0};
    glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px2);

    int green_ok = (px2[0] < 50 && px2[1] > 200 && px2[2] < 50);

    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(2, textures);

    if (check_gl_error("texture_object")) {
	fprintf(stderr, "  FAIL: GL error during texture object test\n");
	g_failed++;
	return;
    }

    if (red_ok && green_ok) {
	printf("  PASS: texture objects work (red=%d,%d,%d  green=%d,%d,%d)\n",
	       px[0], px[1], px[2], px2[0], px2[1], px2[2]);
    } else {
	fprintf(stderr,
		"  FAIL: texture object switching failed "
		"(red=%d,%d,%d  green=%d,%d,%d)\n",
		px[0], px[1], px[2], px2[0], px2[1], px2[2]);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 4: GL_EXT_subtexture  (glTexSubImage2D)                        */
/* ------------------------------------------------------------------ */
static void
test_subtexture(int W, int H)
{
    printf("Test 4: GL_EXT_subtexture\n");

    if (!check_ext("GL_EXT_subtexture"))
	return;

    clear_errors();

    /* Create a 2x2 all-blue texture, then replace the bottom-left with red */
    GLubyte blue[4*4];
    for (int i = 0; i < 4; i++) {
	blue[i*4+0] = 0;
	blue[i*4+1] = 0;
	blue[i*4+2] = 255;
	blue[i*4+3] = 255;
    }
    GLubyte red_patch[4] = { 255, 0, 0, 255 };

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, blue);
    /* Replace bottom-left 1x1 texel with red */
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, red_patch);

    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    /* Sample the red texel (bottom-left = texcoord 0,0) */
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(0.5f, 0.0f); glVertex2f( 1.0f, -1.0f);
    glTexCoord2f(0.5f, 0.5f); glVertex2f( 1.0f,  1.0f);
    glTexCoord2f(0.0f, 0.5f); glVertex2f(-1.0f,  1.0f);
    glEnd();
    glFinish();

    GLubyte px[4] = {0};
    glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);

    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(1, &tex);

    if (check_gl_error("subtexture")) {
	fprintf(stderr, "  FAIL: GL error during subtexture test\n");
	g_failed++;
	return;
    }

    if (px[0] > 200 && px[1] < 50 && px[2] < 50) {
	printf("  PASS: glTexSubImage2D updated texel correctly (%d,%d,%d)\n",
	       px[0], px[1], px[2]);
    } else {
	fprintf(stderr,
		"  FAIL: glTexSubImage2D did not update texel correctly "
		"(expected ~255,0,0 got %d,%d,%d)\n",
		px[0], px[1], px[2]);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 5: GL_EXT_texture3D                                            */
/* ------------------------------------------------------------------ */
static void
test_texture3d(int W, int H)
{
    printf("Test 5: GL_EXT_texture3D\n");

    if (!check_ext("GL_EXT_texture3D"))
	return;

    clear_errors();

    /* Create a 2x2x2 3D texture, first slice red, second slice blue */
    GLubyte data[2*2*2*4];
    for (int z = 0; z < 2; z++) {
	for (int i = 0; i < 4; i++) {
	    int idx = (z*4 + i)*4;
	    data[idx+0] = (z == 0) ? 255 : 0;
	    data[idx+1] = 0;
	    data[idx+2] = (z == 0) ? 0 : 255;
	    data[idx+3] = 255;
	}
    }

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_3D, tex);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, 2, 2, 2, 0,
		 GL_RGBA, GL_UNSIGNED_BYTE, data);

    int created_ok = !check_gl_error("glTexImage3D");

    /* Also test glTexSubImage3D - replace second slice with green */
    if (created_ok) {
	GLubyte green_slice[2*2*4];
	for (int i = 0; i < 4; i++) {
	    green_slice[i*4+0] = 0;
	    green_slice[i*4+1] = 255;
	    green_slice[i*4+2] = 0;
	    green_slice[i*4+3] = 255;
	}
	glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 1, 2, 2, 1,
			GL_RGBA, GL_UNSIGNED_BYTE, green_slice);
    }

    /* Render using 3D texture - sample at r=0.25 (first slice, red) */
    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_3D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glTexCoord3f(0.0f, 0.0f, 0.25f); glVertex2f(-1.0f, -1.0f);
    glTexCoord3f(1.0f, 0.0f, 0.25f); glVertex2f( 1.0f, -1.0f);
    glTexCoord3f(1.0f, 1.0f, 0.25f); glVertex2f( 1.0f,  1.0f);
    glTexCoord3f(0.0f, 1.0f, 0.25f); glVertex2f(-1.0f,  1.0f);
    glEnd();
    glFinish();

    GLubyte px[4] = {0};
    glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);

    glDisable(GL_TEXTURE_3D);
    glDeleteTextures(1, &tex);

    if (check_gl_error("texture3d")) {
	fprintf(stderr, "  FAIL: GL error during texture3D test\n");
	g_failed++;
	return;
    }

    /* First slice should be red */
    if (px[0] > 200 && px[1] < 50 && px[2] < 50) {
	printf("  PASS: 3D texture first slice sampled red (%d,%d,%d)\n",
	       px[0], px[1], px[2]);
    } else {
	fprintf(stderr,
		"  FAIL: 3D texture did not return red for first slice "
		"(got %d,%d,%d)\n",
		px[0], px[1], px[2]);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 6: GL_ARB_multitexture                                         */
/* ------------------------------------------------------------------ */
static void
test_multitexture(int W, int H)
{
    printf("Test 6: GL_ARB_multitexture\n");

    if (!check_ext("GL_ARB_multitexture"))
	return;

    clear_errors();

    /* Create two textures: one red, one that contributes green */
    GLuint tex[2];
    glGenTextures(2, tex);

    GLubyte red[4]    = { 255,   0,   0, 255 };
    GLubyte green[4]  = {   0, 255,   0, 255 };

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, red);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, green);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);

    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);

    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClientActiveTexture(GL_TEXTURE0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glMultiTexCoord2f(GL_TEXTURE0, 0.5f, 0.5f);
    glMultiTexCoord2f(GL_TEXTURE1, 0.5f, 0.5f);
    glVertex2f(-1.0f, -1.0f);
    glMultiTexCoord2f(GL_TEXTURE0, 0.5f, 0.5f);
    glMultiTexCoord2f(GL_TEXTURE1, 0.5f, 0.5f);
    glVertex2f( 1.0f, -1.0f);
    glMultiTexCoord2f(GL_TEXTURE0, 0.5f, 0.5f);
    glMultiTexCoord2f(GL_TEXTURE1, 0.5f, 0.5f);
    glVertex2f( 1.0f,  1.0f);
    glMultiTexCoord2f(GL_TEXTURE0, 0.5f, 0.5f);
    glMultiTexCoord2f(GL_TEXTURE1, 0.5f, 0.5f);
    glVertex2f(-1.0f,  1.0f);
    glEnd();
    glFinish();

    GLubyte px[4] = {0};
    glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);

    /* Disable and clean up */
    glActiveTexture(GL_TEXTURE1);
    glDisable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(2, tex);

    if (check_gl_error("multitexture")) {
	fprintf(stderr, "  FAIL: GL error during multitexture test\n");
	g_failed++;
	return;
    }

    /* With GL_REPLACE on unit 0 (red) and GL_ADD on unit 1 (green),
     * result should have R>0 and G>0 */
    if (px[0] > 100 && px[1] > 100) {
	printf("  PASS: multitexture combine result (%d,%d,%d)\n",
	       px[0], px[1], px[2]);
    } else {
	fprintf(stderr,
		"  FAIL: multitexture combine gave unexpected result (%d,%d,%d)\n",
		px[0], px[1], px[2]);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 7: GL_ARB_texture_compression                                  */
/* ------------------------------------------------------------------ */
static void
test_texture_compression(void)
{
    printf("Test 7: GL_ARB_texture_compression\n");

    if (!check_ext("GL_ARB_texture_compression"))
	return;

    clear_errors();

    /* Query compressed formats */
    GLint num_formats = 0;
    glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB, &num_formats);

    if (check_gl_error("GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB")) {
	fprintf(stderr, "  FAIL: error querying compressed texture formats\n");
	g_failed++;
	return;
    }

    printf("  INFO: %d compressed formats available\n", num_formats);

    /* Test uploading a compressed texture with known data (DXT/S3TC or
     * any supported format).  We first create an uncompressed texture and
     * verify glGetTexLevelParameteriv returns an internal format that is
     * accepted without error; this confirms the path is usable. */
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    /* Use GL_COMPRESSED_RGBA_ARB as a hint - Mesa will choose the format */
    GLubyte data[4*4*4];
    for (int i = 0; i < 16; i++) {
	data[i*4+0] = 100;
	data[i*4+1] = 150;
	data[i*4+2] = 200;
	data[i*4+3] = 255;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_ARB, 4, 4, 0,
		 GL_RGBA, GL_UNSIGNED_BYTE, data);

    if (check_gl_error("glTexImage2D GL_COMPRESSED_RGBA_ARB")) {
	fprintf(stderr, "  FAIL: compressed texture creation failed\n");
	glDeleteTextures(1, &tex);
	g_failed++;
	return;
    }

    GLint compressed = GL_FALSE;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0,
			     GL_TEXTURE_COMPRESSED_ARB, &compressed);
    check_gl_error("GL_TEXTURE_COMPRESSED_ARB query");

    glDeleteTextures(1, &tex);

    printf("  PASS: GL_ARB_texture_compression texture created "
	   "(compressed=%s)\n", compressed ? "yes" : "no");
}

/* ------------------------------------------------------------------ */
/* Test 8: GL_EXT_paletted_texture                                     */
/* ------------------------------------------------------------------ */
static void
test_paletted_texture(int W, int H)
{
    printf("Test 8: GL_EXT_paletted_texture\n");

    if (!check_ext("GL_EXT_paletted_texture"))
	return;

    clear_errors();

    /*
     * Build a 2x2 paletted (COLOR_INDEX8) texture.
     * Palette entry 0 = red, entry 1 = blue.
     * Texels: [0, 1, 1, 0] → top-left and bottom-right are red.
     */
    GLubyte palette[2*4] = {
	255,   0,   0, 255,   /* index 0 = red  */
	  0,   0, 255, 255,   /* index 1 = blue */
    };
    GLubyte indices[2*2] = { 0, 1, 1, 0 };

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    /* Install the palette */
    glColorTableEXT(GL_TEXTURE_2D, GL_RGBA, 2, GL_RGBA, GL_UNSIGNED_BYTE, palette);

    if (check_gl_error("glColorTableEXT")) {
	fprintf(stderr, "  FAIL: glColorTableEXT returned error\n");
	glDeleteTextures(1, &tex);
	g_failed++;
	return;
    }

    /* Upload indexed image */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_COLOR_INDEX8_EXT, 2, 2, 0,
		 GL_COLOR_INDEX, GL_UNSIGNED_BYTE, indices);

    if (check_gl_error("glTexImage2D COLOR_INDEX8_EXT")) {
	fprintf(stderr, "  FAIL: paletted texture upload failed\n");
	glDeleteTextures(1, &tex);
	g_failed++;
	return;
    }

    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    /* Sample index-0 texel (bottom-left), should be red */
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(0.5f, 0.0f); glVertex2f( 1.0f, -1.0f);
    glTexCoord2f(0.5f, 0.5f); glVertex2f( 1.0f,  1.0f);
    glTexCoord2f(0.0f, 0.5f); glVertex2f(-1.0f,  1.0f);
    glEnd();
    glFinish();

    GLubyte px[4] = {0};
    glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);

    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(1, &tex);

    if (check_gl_error("paletted_texture render")) {
	fprintf(stderr, "  FAIL: GL error rendering paletted texture\n");
	g_failed++;
	return;
    }

    if (px[0] > 200 && px[1] < 50 && px[2] < 50) {
	printf("  PASS: paletted texture palette index 0 = red (%d,%d,%d)\n",
	       px[0], px[1], px[2]);
    } else {
	fprintf(stderr,
		"  FAIL: paletted texture palette lookup wrong "
		"(expected ~255,0,0 got %d,%d,%d)\n",
		px[0], px[1], px[2]);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 9: GL_EXT_blend_minmax  (and GL_ARB_imaging blend modes)       */
/* ------------------------------------------------------------------ */
static void
test_blend_minmax(int W, int H)
{
    printf("Test 9: GL_EXT_blend_minmax\n");

    if (!check_ext("GL_EXT_blend_minmax"))
	return;

    clear_errors();

    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);

    /* Clear to a medium gray (128,128,128) */
    glClearColor(128.0f/255.0f, 128.0f/255.0f, 128.0f/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    /* Enable blending with GL_MIN: result should be min of src and dst */
    glEnable(GL_BLEND);
    glBlendEquation(GL_MIN);

    /* Draw a brighter quad (200,200,200) */
    glColor4ub(200, 200, 200, 255);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f( 1.0f, -1.0f);
    glVertex2f( 1.0f,  1.0f);
    glVertex2f(-1.0f,  1.0f);
    glEnd();
    glFinish();

    GLubyte px_min[4] = {0};
    glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px_min);

    /* GL_MIN: result = min(200,128) = 128 (the background stays) */

    /* Now test GL_MAX */
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendEquation(GL_MAX);

    /* Draw a dimmer quad (64,64,64) */
    glColor4ub(64, 64, 64, 255);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f( 1.0f, -1.0f);
    glVertex2f( 1.0f,  1.0f);
    glVertex2f(-1.0f,  1.0f);
    glEnd();
    glFinish();

    GLubyte px_max[4] = {0};
    glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px_max);

    /* GL_MAX: result = max(64,128) = 128 (the background wins) */

    glDisable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    if (check_gl_error("blend_minmax")) {
	fprintf(stderr, "  FAIL: GL error during blend minmax test\n");
	g_failed++;
	return;
    }

    /* GL_MIN test: drawing 200 over 128 background → should stay ~128 */
    int min_ok = (px_min[0] < 150);
    /* GL_MAX test: drawing 64 over 128 background → should stay ~128 */
    int max_ok = (px_max[0] > 100);

    if (min_ok && max_ok) {
	printf("  PASS: GL_MIN=%d (expected ~128), GL_MAX=%d (expected ~128)\n",
	       px_min[0], px_max[0]);
    } else {
	fprintf(stderr,
		"  FAIL: blend minmax: GL_MIN got %d (expected ~128), "
		"GL_MAX got %d (expected ~128)\n",
		px_min[0], px_max[0]);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 10: GL_SGI_color_table                                         */
/* ------------------------------------------------------------------ */
static void
test_sgi_color_table(int W, int H)
{
    printf("Test 10: GL_SGI_color_table\n");

    if (!check_ext("GL_SGI_color_table"))
	return;

    clear_errors();

    /*
     * The GL_SGI_color_table extension provides color table lookup in
     * the PIXEL TRANSFER pipeline (glReadPixels, glDrawPixels, etc.)
     * and also via GL_SGI_texture_color_table for texture fetches.
     *
     * Part A: test GL_COLOR_TABLE applied during glReadPixels.
     *   - Render a bright-red quad (200, 0, 0, 255).
     *   - Install a GL_COLOR_TABLE that maps all R values to exactly 50
     *     and all G/B values to their input (identity for G and B).
     *   - Enable GL_COLOR_TABLE and call glReadPixels.
     *   - Verify R=50, G≈0, B≈0.
     */

    /* Build color table: R-channel → 50; G/B channels → identity */
    GLubyte table[256*4];
    for (int i = 0; i < 256; i++) {
	table[i*4+0] = 50;           /* R always → 50 */
	table[i*4+1] = (GLubyte)i;   /* G → identity  */
	table[i*4+2] = (GLubyte)i;   /* B → identity  */
	table[i*4+3] = 255;
    }

    glColorTable(GL_COLOR_TABLE, GL_RGBA, 256, GL_RGBA, GL_UNSIGNED_BYTE, table);

    if (check_gl_error("glColorTable GL_COLOR_TABLE")) {
	fprintf(stderr, "  FAIL: glColorTable returned error\n");
	g_failed++;
	return;
    }

    /* Render a bright-red quad first (no color table yet) */
    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4ub(200, 0, 0, 255);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f( 1.0f, -1.0f);
    glVertex2f( 1.0f,  1.0f);
    glVertex2f(-1.0f,  1.0f);
    glEnd();
    glFinish();

    /* Read back WITHOUT color table → expect (200, 0, 0) */
    GLubyte px_raw[4] = {0};
    glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px_raw);

    /* Now enable the color table and read again */
    glEnable(GL_COLOR_TABLE);
    GLubyte px_ct[4] = {0};
    glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px_ct);
    glDisable(GL_COLOR_TABLE);

    if (check_gl_error("sgi_color_table")) {
	fprintf(stderr, "  FAIL: GL error during SGI color table test\n");
	g_failed++;
	return;
    }

    /* Without color table: red ~200 */
    int raw_ok = (px_raw[0] > 150);
    /* With color table: R channel mapped to 50 regardless of input */
    int ct_ok = (px_ct[0] > 30 && px_ct[0] < 70);

    if (raw_ok && ct_ok) {
	printf("  PASS: SGI color table pixel transfer: "
	       "raw R=%d, after table R=%d (expected ~50)\n",
	       px_raw[0], px_ct[0]);
    } else {
	fprintf(stderr,
		"  FAIL: SGI color table: raw=(%d,%d,%d) after=(%d,%d,%d) "
		"(raw R expected >150, after R expected ~50)\n",
		px_raw[0], px_raw[1], px_raw[2],
		px_ct[0],  px_ct[1],  px_ct[2]);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 11: GL_ARB_vertex_buffer_object                                */
/* ------------------------------------------------------------------ */
static void
test_vbo(int W, int H)
{
    printf("Test 11: GL_ARB_vertex_buffer_object\n");

    if (!check_ext("GL_ARB_vertex_buffer_object"))
	return;

    clear_errors();

    /* Triangle vertex data: NDC coordinates */
    GLfloat verts[] = {
	 0.0f,  0.8f,
	-0.8f, -0.8f,
	 0.8f, -0.8f,
    };
    GLfloat colors[] = {
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
    };

    GLuint vbo[2];
    glGenBuffers(2, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    if (check_gl_error("VBO creation")) {
	fprintf(stderr, "  FAIL: VBO creation error\n");
	glDeleteBuffers(2, vbo);
	g_failed++;
	return;
    }

    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexPointer(2, GL_FLOAT, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glColorPointer(4, GL_FLOAT, 0, NULL);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glFinish();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(2, vbo);

    GLubyte px[4] = {0};
    glReadPixels(W/2, H/4, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);

    if (check_gl_error("VBO render")) {
	fprintf(stderr, "  FAIL: GL error during VBO render\n");
	g_failed++;
	return;
    }

    /* The centre-bottom area of the triangle should have color */
    if (px[0] > 30 || px[1] > 30 || px[2] > 30) {
	printf("  PASS: VBO rendering produced color (%d,%d,%d)\n",
	       px[0], px[1], px[2]);
    } else {
	fprintf(stderr,
		"  FAIL: VBO rendering produced no color at (%d,%d,%d)\n",
		px[0], px[1], px[2]);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 12: GL_EXT_multi_draw_arrays                                   */
/* ------------------------------------------------------------------ */
static void
test_multi_draw_arrays(int W, int H)
{
    printf("Test 12: GL_EXT_multi_draw_arrays\n");

    if (!check_ext("GL_EXT_multi_draw_arrays"))
	return;

    clear_errors();

    /* Two triangles submitted via glMultiDrawArrays */
    GLfloat verts[] = {
	/* Triangle 0 (left) */
	-0.9f,  0.0f,
	-0.1f,  0.8f,
	-0.1f, -0.8f,
	/* Triangle 1 (right) */
	 0.1f, -0.8f,
	 0.1f,  0.8f,
	 0.9f,  0.0f,
    };

    GLint  first[2]  = { 0, 3 };
    GLsizei count[2] = { 3, 3 };

    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, verts);
    glMultiDrawArrays(GL_TRIANGLES, first, count, 2);
    glFinish();
    glDisableClientState(GL_VERTEX_ARRAY);

    if (check_gl_error("multi_draw_arrays")) {
	fprintf(stderr, "  FAIL: GL error during multi draw arrays\n");
	g_failed++;
	return;
    }

    /* Sample from left triangle and right triangle */
    GLubyte left[4] = {0}, right[4] = {0};
    glReadPixels(W/4,   H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, left);
    glReadPixels(3*W/4, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, right);

    if ((left[0] > 100 || left[1] > 100) &&
	(right[0] > 100 || right[1] > 100)) {
	printf("  PASS: glMultiDrawArrays rendered both triangles "
	       "(L=%d,%d R=%d,%d)\n",
	       left[0], left[1], right[0], right[1]);
    } else {
	fprintf(stderr,
		"  FAIL: glMultiDrawArrays did not render both triangles "
		"(L=%d,%d R=%d,%d)\n",
		left[0], left[1], right[0], right[1]);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 13: GL_ARB_depth_texture                                       */
/* ------------------------------------------------------------------ */
static void
test_depth_texture(int W, int H)
{
    printf("Test 13: GL_ARB_depth_texture\n");

    if (!check_ext("GL_ARB_depth_texture"))
	return;

    clear_errors();

    /*
     * Create a 4x4 depth texture filled with a known value (0.5).
     * Without shadow comparison (GL_TEXTURE_COMPARE_MODE = GL_NONE, the
     * default), the depth value is passed through and rendered as
     * luminance: depth=0.5 → RGBA=(127,127,127,255).
     */
    GLfloat depth_data[4*4];
    for (int i = 0; i < 16; i++)
	depth_data[i] = 0.5f;

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    /* GL_NONE mode: depth passes through as luminance (the default) */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_NONE);
    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_LUMINANCE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 4, 4, 0,
		 GL_DEPTH_COMPONENT, GL_FLOAT, depth_data);

    if (check_gl_error("glTexImage2D GL_DEPTH_COMPONENT")) {
	fprintf(stderr, "  FAIL: depth texture creation failed\n");
	glDeleteTextures(1, &tex);
	g_failed++;
	return;
    }

    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    draw_quad();
    glFinish();

    GLubyte px[4] = {0};
    glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);

    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(1, &tex);

    if (check_gl_error("depth_texture")) {
	fprintf(stderr, "  FAIL: GL error during depth texture test\n");
	g_failed++;
	return;
    }

    /* depth=0.5 rendered as luminance → ~(127,127,127) */
    int ok = (px[0] > 110 && px[0] < 145 &&
	      px[1] > 110 && px[1] < 145 &&
	      px[2] > 110 && px[2] < 145);

    if (ok) {
	printf("  PASS: depth texture sampled as luminance: depth=0.5 → "
	       "(%d,%d,%d) ~gray\n", px[0], px[1], px[2]);
    } else {
	fprintf(stderr,
		"  FAIL: depth texture sampled incorrectly: "
		"depth=0.5 → (%d,%d,%d), expected ~(127,127,127)\n",
		px[0], px[1], px[2]);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 13b: GL_ARB_depth_texture + GL_EXT_framebuffer_object         */
/* Render to an FBO that has a depth texture attached, then verify    */
/* that depth values are correctly written and readable.              */
/* ------------------------------------------------------------------ */
static void
test_fbo_depth_texture(int W, int H)
{
    printf("Test 13b: GL_ARB_depth_texture + FBO interaction\n");

    if (!check_ext("GL_ARB_depth_texture"))
	return;
    if (!check_ext("GL_EXT_framebuffer_object"))
	return;

    clear_errors();

    /* Create a depth texture (initially filled with 1.0) */
    GLuint depth_tex;
    glGenTextures(1, &depth_tex);
    glBindTexture(GL_TEXTURE_2D, depth_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, W, H, 0,
		 GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    /* Create a color texture for the FBO color attachment */
    GLuint color_tex;
    glGenTextures(1, &color_tex);
    glBindTexture(GL_TEXTURE_2D, color_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0,
		 GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    /* Create and bind FBO */
    GLuint fbo;
    glGenFramebuffersEXT(1, &fbo);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,
			      GL_TEXTURE_2D, depth_tex, 0);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
			      GL_TEXTURE_2D, color_tex, 0);

    GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    if (status != GL_FRAMEBUFFER_COMPLETE_EXT) {
	fprintf(stderr, "  SKIP: FBO incomplete (status=0x%x)\n",
		(unsigned)status);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glDeleteFramebuffersEXT(1, &fbo);
	glDeleteTextures(1, &depth_tex);
	glDeleteTextures(1, &color_tex);
	return;
    }

    /* Render a quad at z_ndc=0.5 with GL_ALWAYS depth test.
     * With the default depth range [0,1], a vertex at z_ndc=0.5
     * maps to window depth = (0.5 + 1.0) / 2.0 = 0.75.
     */
    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
    glDepthMask(GL_TRUE);
    glClearDepth(1.0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, -1.0f,  0.5f);
    glVertex3f( 1.0f, -1.0f,  0.5f);
    glVertex3f( 1.0f,  1.0f,  0.5f);
    glVertex3f(-1.0f,  1.0f,  0.5f);
    glEnd();
    glFinish();

    /* Read back the depth value from the FBO */
    GLfloat depth_val = 0.0f;
    glReadPixels(W/2, H/2, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth_val);

    glDisable(GL_DEPTH_TEST);

    /* Restore default framebuffer */
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    glDeleteFramebuffersEXT(1, &fbo);
    glDeleteTextures(1, &depth_tex);
    glDeleteTextures(1, &color_tex);

    if (check_gl_error("test_fbo_depth_texture")) {
	fprintf(stderr, "  FAIL: GL error during FBO depth texture test\n");
	g_failed++;
	return;
    }

    /* depth=0.75 with tolerance for float precision */
    int ok = (depth_val > 0.74f && depth_val < 0.76f);
    if (ok) {
	printf("  PASS: FBO depth texture write/read: depth=%.4f (~0.75)\n",
	       depth_val);
    } else {
	fprintf(stderr,
		"  FAIL: FBO depth texture write/read: depth=%.4f, "
		"expected ~0.75\n", depth_val);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 14: GL_ARB_shadow                                              */
/* ------------------------------------------------------------------ */
static void
test_shadow(int W, int H)
{
    printf("Test 14: GL_ARB_shadow\n");

    if (!check_ext("GL_ARB_shadow"))
	return;

    clear_errors();

    /*
     * Create a depth texture and fill it with a known depth value (0.5).
     * Enable shadow comparison (GL_COMPARE_R_TO_TEXTURE_ARB, GL_LEQUAL).
     * When the texture coordinate R <= stored depth → result = 1.0 (lit).
     * When R > stored depth → result = 0.0 (in shadow).
     */
    GLuint depth_tex;
    glGenTextures(1, &depth_tex);
    glBindTexture(GL_TEXTURE_2D, depth_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    /* Set comparison mode */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB,
		    GL_COMPARE_R_TO_TEXTURE_ARB);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

    /* Fill a 4x4 depth texture with 0.5 */
    GLfloat depth_data[4*4];
    for (int i = 0; i < 16; i++)
	depth_data[i] = 0.5f;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 4, 4, 0,
		 GL_DEPTH_COMPONENT, GL_FLOAT, depth_data);

    if (check_gl_error("shadow depth texture creation")) {
	fprintf(stderr, "  FAIL: shadow depth texture creation failed\n");
	glDeleteTextures(1, &depth_tex);
	g_failed++;
	return;
    }

    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    /*
     * First pass: R=0.3 → 0.3 <= 0.5 → comparison passes → result=1 (white)
     */
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glTexCoord3f(0.5f, 0.5f, 0.3f); glVertex2f(-1.0f, -1.0f);
    glTexCoord3f(0.5f, 0.5f, 0.3f); glVertex2f( 1.0f, -1.0f);
    glTexCoord3f(0.5f, 0.5f, 0.3f); glVertex2f( 1.0f,  1.0f);
    glTexCoord3f(0.5f, 0.5f, 0.3f); glVertex2f(-1.0f,  1.0f);
    glEnd();
    glFinish();

    GLubyte px_lit[4] = {0};
    glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px_lit);

    /*
     * Second pass: R=0.8 → 0.8 > 0.5 → comparison fails → result=0 (black)
     */
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glTexCoord3f(0.5f, 0.5f, 0.8f); glVertex2f(-1.0f, -1.0f);
    glTexCoord3f(0.5f, 0.5f, 0.8f); glVertex2f( 1.0f, -1.0f);
    glTexCoord3f(0.5f, 0.5f, 0.8f); glVertex2f( 1.0f,  1.0f);
    glTexCoord3f(0.5f, 0.5f, 0.8f); glVertex2f(-1.0f,  1.0f);
    glEnd();
    glFinish();

    GLubyte px_shadow[4] = {0};
    glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px_shadow);

    glDisable(GL_TEXTURE_2D);
    glDeleteTextures(1, &depth_tex);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    if (check_gl_error("shadow")) {
	fprintf(stderr, "  FAIL: GL error during shadow test\n");
	g_failed++;
	return;
    }

    /* Lit pass: all channels should be high (white) */
    int lit_ok     = (px_lit[0]    > 150);
    /* Shadow pass: all channels should be low (black) */
    int shadow_ok  = (px_shadow[0] < 100);

    if (lit_ok && shadow_ok) {
	printf("  PASS: shadow comparison lit=%d shadow=%d\n",
	       px_lit[0], px_shadow[0]);
    } else {
	fprintf(stderr,
		"  FAIL: shadow comparison lit=%d (expected >150) "
		"shadow=%d (expected <100)\n",
		px_lit[0], px_shadow[0]);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 15: GL_EXT_texture_rectangle                                   */
/* ------------------------------------------------------------------ */
static void
test_texture_rectangle(int W, int H)
{
    printf("Test 15: GL_EXT_texture_rectangle\n");

    /* Either EXT or ARB flavor is fine */
    const char *exts = (const char *)glGetString(GL_EXTENSIONS);
    if (!exts ||
	(!strstr(exts, "GL_EXT_texture_rectangle") &&
	 !strstr(exts, "GL_ARB_texture_rectangle") &&
	 !strstr(exts, "GL_NV_texture_rectangle"))) {
	fprintf(stderr, "  SKIP: GL_EXT_texture_rectangle not advertised\n");
	return;
    }

    clear_errors();

    int TW = 4, TH = 4;

    /* Fill texture with a gradient: row 0 = red .. row 3 = blue */
    GLubyte data[4*4*4];
    for (int y = 0; y < TH; y++) {
	for (int x = 0; x < TW; x++) {
	    int idx = (y*TW + x)*4;
	    data[idx+0] = (GLubyte)(255 - y*64);
	    data[idx+1] = 0;
	    data[idx+2] = (GLubyte)(y*64);
	    data[idx+3] = 255;
	}
    }

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, tex);
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    /* Rectangle textures do not support mipmaps or most wrap modes */
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, TW, TH, 0,
		 GL_RGBA, GL_UNSIGNED_BYTE, data);

    if (check_gl_error("glTexImage2D GL_TEXTURE_RECTANGLE_ARB")) {
	fprintf(stderr, "  FAIL: rectangle texture creation failed\n");
	glDeleteTextures(1, &tex);
	g_failed++;
	return;
    }

    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_RECTANGLE_ARB);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    /* Rectangle textures use integer (pixel) coordinates, not [0,1] */
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    /* Use non-normalized coords (0..TW, 0..TH) */
    glTexCoord2f(0.0f,  0.0f); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f((float)TW, 0.0f); glVertex2f( 1.0f, -1.0f);
    glTexCoord2f((float)TW, (float)TH); glVertex2f( 1.0f,  1.0f);
    glTexCoord2f(0.0f,  (float)TH); glVertex2f(-1.0f,  1.0f);
    glEnd();
    glFinish();

    GLubyte px_bot[4] = {0};
    glReadPixels(W/2, 2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px_bot);

    glDisable(GL_TEXTURE_RECTANGLE_ARB);
    glDeleteTextures(1, &tex);

    if (check_gl_error("texture_rectangle")) {
	fprintf(stderr, "  FAIL: GL error during texture rectangle test\n");
	g_failed++;
	return;
    }

    /* Bottom of screen → row 0 texels → red dominant */
    if (px_bot[0] > 150 && px_bot[2] < 100) {
	printf("  PASS: rectangle texture bottom row red (%d,%d,%d)\n",
	       px_bot[0], px_bot[1], px_bot[2]);
    } else {
	fprintf(stderr,
		"  FAIL: rectangle texture bottom row expected red, "
		"got (%d,%d,%d)\n",
		px_bot[0], px_bot[1], px_bot[2]);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 16: GL_ARB_vertex_program                                      */
/* ------------------------------------------------------------------ */
static void
test_vertex_program(int W, int H)
{
    printf("Test 16: GL_ARB_vertex_program\n");

    if (!check_ext("GL_ARB_vertex_program"))
	return;

    clear_errors();

    /* Minimal ARB vertex program that passes position through */
    static const char vp_src[] =
	"!!ARBvp1.0\n"
	"ATTRIB iPos = vertex.position;\n"
	"OUTPUT oPos = result.position;\n"
	"MOV oPos, iPos;\n"
	"MOV result.color, {1.0, 0.5, 0.0, 1.0};\n"
	"END\n";

    GLuint vp;
    glGenProgramsARB(1, &vp);
    glBindProgramARB(GL_VERTEX_PROGRAM_ARB, vp);
    glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB,
		       (GLsizei)strlen(vp_src), vp_src);

    GLint errPos = -1;
    glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &errPos);
    if (errPos != -1) {
	const GLubyte *errStr = glGetString(GL_PROGRAM_ERROR_STRING_ARB);
	fprintf(stderr, "  FAIL: ARB vertex program error at %d: %s\n",
		errPos, errStr ? (const char *)errStr : "(null)");
	glDeleteProgramsARB(1, &vp);
	g_failed++;
	return;
    }

    glEnable(GL_VERTEX_PROGRAM_ARB);
    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glVertex2f( 0.0f,  0.8f);
    glVertex2f(-0.8f, -0.8f);
    glVertex2f( 0.8f, -0.8f);
    glEnd();
    glFinish();

    glDisable(GL_VERTEX_PROGRAM_ARB);
    glDeleteProgramsARB(1, &vp);

    GLubyte px[4] = {0};
    glReadPixels(W/2, H/4, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);

    if (check_gl_error("vertex_program")) {
	fprintf(stderr, "  FAIL: GL error during vertex program test\n");
	g_failed++;
	return;
    }

    /* Program outputs orange (1.0, 0.5, 0.0) */
    if (px[0] > 200 && px[1] > 80 && px[2] < 50) {
	printf("  PASS: ARB vertex program output orange (%d,%d,%d)\n",
	       px[0], px[1], px[2]);
    } else {
	fprintf(stderr,
		"  FAIL: ARB vertex program output (%d,%d,%d) "
		"expected ~(255,127,0)\n",
		px[0], px[1], px[2]);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 17: GL_ARB_fragment_program                                    */
/* ------------------------------------------------------------------ */
static void
test_fragment_program(int W, int H)
{
    printf("Test 17: GL_ARB_fragment_program\n");

    if (!check_ext("GL_ARB_fragment_program"))
	return;

    clear_errors();

    /* Minimal ARB fragment program that outputs a fixed cyan color */
    static const char fp_src[] =
	"!!ARBfp1.0\n"
	"MOV result.color, {0.0, 1.0, 1.0, 1.0};\n"
	"END\n";

    GLuint fp;
    glGenProgramsARB(1, &fp);
    glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, fp);
    glProgramStringARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB,
		       (GLsizei)strlen(fp_src), fp_src);

    GLint errPos = -1;
    glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &errPos);
    if (errPos != -1) {
	const GLubyte *errStr = glGetString(GL_PROGRAM_ERROR_STRING_ARB);
	fprintf(stderr, "  FAIL: ARB fragment program error at %d: %s\n",
		errPos, errStr ? (const char *)errStr : "(null)");
	glDeleteProgramsARB(1, &fp);
	g_failed++;
	return;
    }

    glEnable(GL_FRAGMENT_PROGRAM_ARB);
    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f( 1.0f, -1.0f);
    glVertex2f( 1.0f,  1.0f);
    glVertex2f(-1.0f,  1.0f);
    glEnd();
    glFinish();

    glDisable(GL_FRAGMENT_PROGRAM_ARB);
    glDeleteProgramsARB(1, &fp);

    GLubyte px[4] = {0};
    glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);

    if (check_gl_error("fragment_program")) {
	fprintf(stderr, "  FAIL: GL error during fragment program test\n");
	g_failed++;
	return;
    }

    /* Program outputs cyan (0.0, 1.0, 1.0) */
    if (px[0] < 50 && px[1] > 200 && px[2] > 200) {
	printf("  PASS: ARB fragment program output cyan (%d,%d,%d)\n",
	       px[0], px[1], px[2]);
    } else {
	fprintf(stderr,
		"  FAIL: ARB fragment program output (%d,%d,%d) "
		"expected ~(0,255,255)\n",
		px[0], px[1], px[2]);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 18: GL_ARB_shader_objects / GL_ARB_vertex_shader               */
/* ------------------------------------------------------------------ */
static void
test_glsl_shader(int W, int H)
{
    printf("Test 18: GL_ARB_shader_objects / GL_ARB_vertex_shader\n");

    if (!check_ext("GL_ARB_shader_objects") ||
	!check_ext("GL_ARB_vertex_shader"))
	return;

    clear_errors();

    const char *vert =
	"#version 110\n"
	"void main() {\n"
	"    gl_Position = gl_Vertex;\n"
	"    gl_FrontColor = gl_Color;\n"
	"}\n";
    const char *frag =
	"#version 110\n"
	"void main() {\n"
	"    gl_FragColor = gl_Color;\n"
	"}\n";

    GLuint prog = make_program(vert, frag);
    if (!prog) {
	fprintf(stderr, "  FAIL: GLSL program compilation/link failed\n");
	g_failed++;
	return;
    }

    glUseProgram(prog);
    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);   /* blue via vertex color */
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f( 1.0f, -1.0f);
    glVertex2f( 1.0f,  1.0f);
    glVertex2f(-1.0f,  1.0f);
    glEnd();
    glFinish();

    glUseProgram(0);
    glDeleteProgram(prog);

    GLubyte px[4] = {0};
    glReadPixels(W/2, H/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);

    if (check_gl_error("glsl_shader")) {
	fprintf(stderr, "  FAIL: GL error during GLSL shader test\n");
	g_failed++;
	return;
    }

    if (px[0] < 50 && px[1] < 50 && px[2] > 200) {
	printf("  PASS: GLSL shader output blue (%d,%d,%d)\n",
	       px[0], px[1], px[2]);
    } else {
	fprintf(stderr,
		"  FAIL: GLSL shader output (%d,%d,%d) expected ~(0,0,255)\n",
		px[0], px[1], px[2]);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* Test 19: GL_ARB_occlusion_query                                     */
/* ------------------------------------------------------------------ */
static void
test_occlusion_query(int W, int H)
{
    printf("Test 19: GL_ARB_occlusion_query\n");

    if (!check_ext("GL_ARB_occlusion_query"))
	return;

    clear_errors();

    GLuint queries[2];
    glGenQueriesARB(2, queries);

    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
     * With identity matrices, vertex z values are NDC z directly.
     * z_ndc → z_window = (z_ndc + 1) / 2:
     *   z_ndc =  0.0 → depth = 0.5
     *   z_ndc =  0.5 → depth = 0.75   (farther; fails GL_LEQUAL after 0.5 written)
     *
     * Query 0: render a visible full-screen quad at z_ndc=0 → should pass many samples
     */
    glBeginQueryARB(GL_SAMPLES_PASSED_ARB, queries[0]);
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, -1.0f,  0.0f);
    glVertex3f( 1.0f, -1.0f,  0.0f);
    glVertex3f( 1.0f,  1.0f,  0.0f);
    glVertex3f(-1.0f,  1.0f,  0.0f);
    glEnd();
    glEndQueryARB(GL_SAMPLES_PASSED_ARB);

    /*
     * Query 1: render a full-screen quad at z_ndc=0.5 (depth=0.75).
     * Stored depth is 0.5 (from previous quad).
     * GL_LEQUAL: 0.75 <= 0.5 is FALSE → all fragments rejected → 0 samples.
     */
    glBeginQueryARB(GL_SAMPLES_PASSED_ARB, queries[1]);
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, -1.0f,  0.5f);
    glVertex3f( 1.0f, -1.0f,  0.5f);
    glVertex3f( 1.0f,  1.0f,  0.5f);
    glVertex3f(-1.0f,  1.0f,  0.5f);
    glEnd();
    glEndQueryARB(GL_SAMPLES_PASSED_ARB);

    glFinish();
    glDisable(GL_DEPTH_TEST);

    GLuint result0 = 0, result1 = 0;
    glGetQueryObjectuivARB(queries[0], GL_QUERY_RESULT_ARB, &result0);
    glGetQueryObjectuivARB(queries[1], GL_QUERY_RESULT_ARB, &result1);

    glDeleteQueriesARB(2, queries);

    if (check_gl_error("occlusion_query")) {
	fprintf(stderr, "  FAIL: GL error during occlusion query test\n");
	g_failed++;
	return;
    }

    if (result0 > 0 && result1 == 0) {
	printf("  PASS: occlusion query visible=%u occluded=%u\n",
	       result0, result1);
    } else {
	fprintf(stderr,
		"  FAIL: occlusion query visible=%u (expected >0) "
		"occluded=%u (expected 0)\n",
		result0, result1);
	g_failed++;
    }
}

/* ------------------------------------------------------------------ */
/* main                                                                */
/* ------------------------------------------------------------------ */

int
main(void)
{
    int W = 64, H = 64;

    /* 16-bit depth: sufficient precision for all depth/shadow/occlusion tests */
    OSMesaContext ctx = OSMesaCreateContextExt(OSMESA_RGBA, 16, 0, 0, NULL);
    if (!ctx) {
	fprintf(stderr, "OSMesaCreateContext failed\n");
	return 1;
    }

    GLubyte *fb = (GLubyte *)calloc(W * H * 4, sizeof(GLubyte));
    if (!fb) {
	fprintf(stderr, "Out of memory\n");
	OSMesaDestroyContext(ctx);
	return 1;
    }

    if (!OSMesaMakeCurrent(ctx, fb, GL_UNSIGNED_BYTE, W, H)) {
	fprintf(stderr, "OSMesaMakeCurrent failed\n");
	free(fb);
	OSMesaDestroyContext(ctx);
	return 1;
    }
    OSMesaPixelStore(OSMESA_Y_UP, 0);

    printf("OpenGL renderer: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version:  %s\n", glGetString(GL_VERSION));
    printf("\n");

    test_extension_strings();
    test_polygon_offset(W, H);
    test_texture_object(W, H);
    test_subtexture(W, H);
    test_texture3d(W, H);
    test_multitexture(W, H);
    test_texture_compression();
    test_paletted_texture(W, H);
    test_blend_minmax(W, H);
    test_sgi_color_table(W, H);
    test_vbo(W, H);
    test_multi_draw_arrays(W, H);
    test_depth_texture(W, H);
    test_fbo_depth_texture(W, H);
    test_shadow(W, H);
    test_texture_rectangle(W, H);
    test_vertex_program(W, H);
    test_fragment_program(W, H);
    test_glsl_shader(W, H);
    test_occlusion_query(W, H);

    printf("\n");
    if (g_failed == 0) {
	printf("All tests PASSED\n");
    } else {
	printf("%d test(s) FAILED\n", g_failed);
    }

    free(fb);
    OSMesaDestroyContext(ctx);

    return g_failed ? 1 : 0;
}

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8 cino=N-s
 */
