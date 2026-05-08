#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "OSMesa/gl.h"
#include "OSMesa/osmesa.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static double
now_seconds(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
}

static void
set_perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    GLdouble ymax = zNear * tan(fovy * M_PI / 360.0);
    GLdouble xmax = ymax * aspect;
    glFrustum(-xmax, xmax, -ymax, ymax, zNear, zFar);
}

static void
draw_triangle(GLfloat angle)
{
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.85f, -0.70f, -0.35f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.85f, -0.70f, 0.10f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.95f, 0.65f);
    glEnd();
}

static void
draw_scene(GLint width, GLint height, GLint instances, GLint frame)
{
    GLint side;
    GLint row;
    GLint col;
    GLfloat aspect = (GLfloat) width / (GLfloat) height;
    GLfloat spacing;
    GLfloat base_angle;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    set_perspective(65.0, aspect, 1.0, 150.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -45.0f);
    glRotatef(-18.0f, 1.0f, 0.0f, 0.0f);

    side = 1;
    while (side * side < instances) {
	side++;
    }

    spacing = 3.35f;
    base_angle = (GLfloat) frame * 1.75f;

    for (row = 0; row < side; row++) {
	for (col = 0; col < side; col++) {
	    GLint index = row * side + col;
	    GLfloat tx;
	    GLfloat ty;
	    GLfloat tz;
	    GLfloat angle;

	    if (index >= instances)
		break;

	    tx = ((GLfloat) col - ((GLfloat) side - 1.0f) * 0.5f) * spacing;
	    ty = ((GLfloat) row - ((GLfloat) side - 1.0f) * 0.5f) * spacing;
	    tz = -8.0f + 3.25f * (GLfloat) sin((GLfloat) index * 0.17f
					      + (GLfloat) frame * 0.09f);
	    angle = base_angle + (GLfloat) index * 11.0f;

	    glPushMatrix();
	    glTranslatef(tx, ty, tz);
	    draw_triangle(angle);
	    glPopMatrix();
	}
    }
}

static unsigned long
compute_checksum(const GLubyte *buffer, size_t bytes)
{
    size_t i;
    unsigned long checksum = 2166136261u;
    size_t stride = bytes / 4096;

    if (stride == 0)
	stride = 1;

    for (i = 0; i < bytes; i += stride) {
	checksum ^= buffer[i];
	checksum *= 16777619u;
    }

    return checksum;
}

static int
parse_int_arg(const char *name, const char *value, GLint *out)
{
    char *end = NULL;
    long parsed = strtol(value, &end, 10);
    if (!value[0] || (end && *end) || parsed <= 0 || parsed > 1L << 30) {
	fprintf(stderr, "invalid value for %s: %s\n", name, value);
	return 0;
    }
    *out = (GLint) parsed;
    return 1;
}

int
main(int argc, char **argv)
{
    GLint width = 640;
    GLint height = 480;
    GLint depth_bits = 32;
    GLint frames = 600;
    GLint warmup = 60;
    GLint instances = 256;
    GLint i;
    OSMesaContext ctx;
    GLubyte *framebuffer;
    double start_time;
    double end_time;
    double elapsed;
    double fps;
    double triangles_per_second;
    unsigned long checksum;

    for (i = 1; i < argc; i++) {
	if (strcmp(argv[i], "--width") == 0 && i + 1 < argc) {
	    if (!parse_int_arg("--width", argv[++i], &width))
		return 1;
	} else if (strcmp(argv[i], "--height") == 0 && i + 1 < argc) {
	    if (!parse_int_arg("--height", argv[++i], &height))
		return 1;
	} else if (strcmp(argv[i], "--depth") == 0 && i + 1 < argc) {
	    if (!parse_int_arg("--depth", argv[++i], &depth_bits))
		return 1;
	} else if (strcmp(argv[i], "--frames") == 0 && i + 1 < argc) {
	    if (!parse_int_arg("--frames", argv[++i], &frames))
		return 1;
	} else if (strcmp(argv[i], "--warmup") == 0 && i + 1 < argc) {
	    if (!parse_int_arg("--warmup", argv[++i], &warmup))
		return 1;
	} else if (strcmp(argv[i], "--instances") == 0 && i + 1 < argc) {
	    if (!parse_int_arg("--instances", argv[++i], &instances))
		return 1;
	} else if (strcmp(argv[i], "--help") == 0) {
	    printf("usage: %s [--width N] [--height N] [--depth 16|24|32]"
		   " [--frames N] [--warmup N] [--instances N]\n", argv[0]);
	    return 0;
	} else {
	    fprintf(stderr, "unknown argument: %s\n", argv[i]);
	    return 1;
	}
    }

    if (depth_bits != 16 && depth_bits != 24 && depth_bits != 32) {
	fprintf(stderr, "depth must be 16, 24, or 32\n");
	return 1;
    }

    ctx = OSMesaCreateContextExt(OSMESA_RGBA, depth_bits, 0, 0, NULL);
    if (!ctx) {
	fprintf(stderr, "OSMesaCreateContextExt failed\n");
	return 1;
    }

    framebuffer = (GLubyte *) calloc((size_t) width * height * 4, sizeof(GLubyte));
    if (!framebuffer) {
	fprintf(stderr, "framebuffer allocation failed\n");
	OSMesaDestroyContext(ctx);
	return 1;
    }

    if (!OSMesaMakeCurrent(ctx, framebuffer, GL_UNSIGNED_BYTE, width, height)) {
	fprintf(stderr, "OSMesaMakeCurrent failed\n");
	free(framebuffer);
	OSMesaDestroyContext(ctx);
	return 1;
    }

    glClearColor(0.05f, 0.10f, 0.15f, 1.0f);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_DITHER);
    glDisable(GL_CULL_FACE);

    for (i = 0; i < warmup; i++) {
	draw_scene(width, height, instances, i);
	glFinish();
    }

    start_time = now_seconds();
    for (i = 0; i < frames; i++) {
	draw_scene(width, height, instances, warmup + i);
	glFinish();
    }
    end_time = now_seconds();

    elapsed = end_time - start_time;
    fps = (double) frames / elapsed;
    triangles_per_second = ((double) frames * (double) instances) / elapsed;
    checksum = compute_checksum(framebuffer, (size_t) width * height * 4);

    printf("depth=%d frames=%d warmup=%d size=%dx%d instances=%d "
	   "elapsed=%.6f fps=%.2f triangles_per_sec=%.2f checksum=%lu\n",
	   depth_bits, frames, warmup, width, height, instances,
	   elapsed, fps, triangles_per_second, checksum);

    free(framebuffer);
    OSMesaDestroyContext(ctx);
    return 0;
}
