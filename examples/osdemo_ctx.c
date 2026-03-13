/*
 * Demo of explicit-context OSMesa rendering via glctx.h
 *
 * This demonstrates the zero-TLS API introduced by the GLcontext * refactor.
 * Every GL call is made through osCtx<Func>(ctx, ...) wrappers that route
 * directly through the context's dispatch table without touching any global
 * or thread-local state.
 *
 * Two OSMesa contexts are used independently in the same process to show
 * that they do not interfere with each other.
 *
 * This program is in the public domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "OSMesa/glctx.h"

#ifndef M_PI
#define M_PI 3.14159265
#endif

#define WIDTH  400
#define HEIGHT 400

/* Minimal PNG writer (svpng) - same helper used in osdemo.c */
#include "svpng.h"

static void
write_png(const char *filename, const GLubyte *buf, int width, int height)
{
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "osdemo_ctx: cannot open %s\n", filename);
        return;
    }
    svpng(fp, (unsigned)width, (unsigned)height,
          (const unsigned char *)buf, 1 /*alpha*/);
    fclose(fp);
    printf("Wrote %s\n", filename);
}


/*
 * Render a simple scene into the supplied context/buffer using the
 * explicit-context API (osCtx* wrappers).  No MakeCurrent is called.
 */
static void
render_scene(OSMesaContext ctx, GLfloat r, GLfloat g, GLfloat b)
{
    /* --- Setup --- */
    osCtxViewport(ctx, 0, 0, WIDTH, HEIGHT);

    osCtxMatrixMode(ctx, GL_PROJECTION);
    osCtxLoadIdentity(ctx);
    osCtxFrustum(ctx, -1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

    osCtxMatrixMode(ctx, GL_MODELVIEW);
    osCtxLoadIdentity(ctx);

    /* --- Clear to the requested background colour --- */
    osCtxClearColor(ctx, r * 0.2f, g * 0.2f, b * 0.2f, 1.0f);
    osCtxClear(ctx, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* --- Lighting --- */
    osCtxEnable(ctx, GL_LIGHTING);
    osCtxEnable(ctx, GL_LIGHT0);
    osCtxEnable(ctx, GL_DEPTH_TEST);

    {
        GLfloat pos[]   = { 1.0f, 1.0f, 1.0f, 0.0f };
        GLfloat color[] = { r, g, b, 1.0f };
        GLfloat white[] = { 0.8f, 0.8f, 0.8f, 1.0f };
        osCtxLightfv(ctx, GL_LIGHT0, GL_POSITION, pos);
        osCtxLightfv(ctx, GL_LIGHT0, GL_DIFFUSE,  color);
        osCtxLightfv(ctx, GL_LIGHT0, GL_SPECULAR, white);
        osCtxMaterialfv(ctx, GL_FRONT_AND_BACK, GL_DIFFUSE, color);
    }

    /* --- Draw a simple quad (two triangles) as stand-in geometry --- */
    osCtxTranslatef(ctx, 0.0f, 0.0f, -5.0f);
    osCtxRotatef(ctx, 30.0f, 1.0f, 0.5f, 0.0f);

    osCtxBegin(ctx, GL_TRIANGLES);
    osCtxNormal3f(ctx,  0.0f, 0.0f, 1.0f);
    osCtxVertex3f(ctx, -1.0f, -1.0f, 0.0f);
    osCtxVertex3f(ctx,  1.0f, -1.0f, 0.0f);
    osCtxVertex3f(ctx,  1.0f,  1.0f, 0.0f);

    osCtxVertex3f(ctx, -1.0f, -1.0f, 0.0f);
    osCtxVertex3f(ctx,  1.0f,  1.0f, 0.0f);
    osCtxVertex3f(ctx, -1.0f,  1.0f, 0.0f);
    osCtxEnd(ctx);

    osCtxFinish(ctx);
}


int main(int argc, char *argv[])
{
    GLubyte *buf1 = (GLubyte *)malloc(WIDTH * HEIGHT * 4);
    GLubyte *buf2 = (GLubyte *)malloc(WIDTH * HEIGHT * 4);

    if (!buf1 || !buf2) {
        fprintf(stderr, "osdemo_ctx: out of memory\n");
        return 1;
    }

    /* --- Create two independent contexts --- */
    OSMesaContext ctx1 = OSMesaCreateContext(OSMESA_RGBA, NULL);
    OSMesaContext ctx2 = OSMesaCreateContext(OSMESA_RGBA, NULL);

    if (!ctx1 || !ctx2) {
        fprintf(stderr, "osdemo_ctx: OSMesaCreateContext failed\n");
        return 1;
    }

    /* Bind each context to its own framebuffer once so internal state
     * (viewport, dispatch, etc.) is initialised.  After this we never call
     * MakeCurrent again - all rendering uses osCtx* directly. */
    if (!OSMesaMakeCurrent(ctx1, buf1, GL_UNSIGNED_BYTE, WIDTH, HEIGHT)) {
        fprintf(stderr, "osdemo_ctx: OSMesaMakeCurrent failed for ctx1\n");
        return 1;
    }
    OSMesaSetCurrentContext(NULL);   /* unbind - no global current context */

    if (!OSMesaMakeCurrent(ctx2, buf2, GL_UNSIGNED_BYTE, WIDTH, HEIGHT)) {
        fprintf(stderr, "osdemo_ctx: OSMesaMakeCurrent failed for ctx2\n");
        return 1;
    }
    OSMesaSetCurrentContext(NULL);   /* unbind again */

    printf("Rendering ctx1 (red scene)  via explicit context API...\n");
    render_scene(ctx1, 1.0f, 0.2f, 0.2f);

    printf("Rendering ctx2 (blue scene) via explicit context API...\n");
    render_scene(ctx2, 0.2f, 0.2f, 1.0f);

    write_png("osdemo_ctx1.png", buf1, WIDTH, HEIGHT);
    write_png("osdemo_ctx2.png", buf2, WIDTH, HEIGHT);

    OSMesaDestroyContext(ctx1);
    OSMesaDestroyContext(ctx2);
    free(buf1);
    free(buf2);

    printf("osdemo_ctx: done.  No global GL context was ever current during rendering.\n");
    return 0;
}
