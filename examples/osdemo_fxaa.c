/*
 * FXAA demonstration for OSMesa
 *
 * This example renders aliasing-prone 2D geometry (thin high-contrast edges,
 * rotated bars, single-pixel lines, and a fine checker grid) and applies a CPU
 * FXAA filter ported from VTK's `vtkFXAAFilterFS.glsl`. It writes three
 * images:
 *
 *   <base>_nofxaa.png   — original render
 *   <base>_fxaa.png     — FXAA filtered render
 *   <base>_compare.png  — side-by-side (left = no FXAA, right = FXAA)
 *
 * Usage:
 *   osdemo_fxaa <base_filename> [width height]
 *
 * FXAA parameters match typical VTK usage and favor visible edge smoothing
 * while preserving detail:
 * - RelativeContrastThreshold: `0.125`
 * - HardContrastThreshold: `0.0625`
 * - SubpixelBlendLimit: `0.75`
 * - SubpixelContrastThreshold: `0.25`
 * - EndpointSearchIterations: `12`
 */

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "OSMesa/gl.h"
#include "OSMesa/osmesa.h"
#include "svpng.h"

/* Write PNG via svpng (expects RGBA8 buffer, stride = width*4) */
static void write_png(const char *filename, const unsigned char *buffer, int width, int height)
{
    FILE *f = fopen(filename, "wb");
    if (!f) {
        fprintf(stderr, "Failed to open '%s' for writing\n", filename);
        return;
    }
    svpng(f, width, height, buffer, 1);
    fclose(f);
}

/* Render a 2D scene tailored to generate aliasing on high-contrast edges */
static void render_aliasing_scene(int Width, int Height)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

#ifdef GL_MULTISAMPLE
    glDisable(GL_MULTISAMPLE);
#endif

    glViewport(0, 0, Width, Height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble)Width, 0.0, (GLdouble)Height, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* 1) Rotated thin white bar (long diagonal edges) */
    glPushMatrix();
    glTranslatef(Width * 0.5f, Height * 0.65f, 0.0f);
    glRotatef(17.0f, 0.f, 0.f, 1.f);
    glColor3f(1.f, 1.f, 1.f);
    glBegin(GL_QUADS);
        glVertex2f(-180.f, -6.f);
        glVertex2f( 180.f, -6.f);
        glVertex2f( 180.f,  6.f);
        glVertex2f(-180.f,  6.f);
    glEnd();
    glPopMatrix();

    /* 2) Single-pixel lines at multiple shallow angles around center */
    glLineWidth(1.f);
    glColor3f(1.f, 1.f, 0.f);
    glBegin(GL_LINES);
    const float cx = Width * 0.3f, cy = Height * 0.35f;
    for (int a = 10; a <= 80; a += 10) {
        float rad = (float)a * (float)M_PI / 180.0f;
        float len = (float)(Width * 0.35f);
        float dx = cosf(rad) * len;
        float dy = sinf(rad) * len;
        glVertex2f(cx - dx * 0.5f, cy - dy * 0.5f);
        glVertex2f(cx + dx * 0.5f, cy + dy * 0.5f);
    }
    glEnd();

    /* 3) Fine wireframe box rotated slightly to force subpixel edges */
    glPushMatrix();
    glTranslatef(Width * 0.7f, Height * 0.35f, 0.0f);
    glRotatef(-13.0f, 0.f, 0.f, 1.f);
    glColor3f(0.f, 1.f, 1.f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-120.f, -90.f);
        glVertex2f( 120.f, -90.f);
        glVertex2f( 120.f,  90.f);
        glVertex2f(-120.f,  90.f);
    glEnd();

    /* Internal wireframe grid */
    glColor3f(0.f, 1.f, 1.f);
    glBegin(GL_LINES);
    for (int i = -100; i <= 100; i += 10) {
        glVertex2f((float)i, -90.f);
        glVertex2f((float)i,  90.f);
    }
    for (int j = -80; j <= 80; j += 10) {
        glVertex2f(-120.f, (float)j);
        glVertex2f( 120.f, (float)j);
    }
    glEnd();
    glPopMatrix();

    /* 4) A small rotated checker region (alternating quads) for subpixel aliasing */
    glPushMatrix();
    glTranslatef(Width * 0.5f, Height * 0.25f, 0.0f);
    glRotatef(7.0f, 0.f, 0.f, 1.f);
    const int cw = 6, ch = 6, cols = 26, rows = 18;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            int parity = (x + y) & 1;
            glColor3f(parity ? 1.f : 0.f, parity ? 1.f : 0.f, parity ? 1.f : 0.f);
            float x0 = (float)(x * cw) - (float)(cols * cw) * 0.5f;
            float y0 = (float)(y * ch) - (float)(rows * ch) * 0.5f;
            float x1 = x0 + cw, y1 = y0 + ch;
            glBegin(GL_QUADS);
                glVertex2f(x0, y0);
                glVertex2f(x1, y0);
                glVertex2f(x1, y1);
                glVertex2f(x0, y1);
            glEnd();
        }
    }
    glPopMatrix();

    glFinish();
}

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage:\n  osdemo_fxaa <base_filename> [width height]\n");
        fprintf(stderr, "\nThis demo now uses the integrated OSMesa FXAA feature.\n");
        fprintf(stderr, "It writes:\n");
        fprintf(stderr, "  <base>_nofxaa.png   - original render (no FXAA)\n");
        fprintf(stderr, "  <base>_fxaa.png     - FXAA with sRGB conversion (matching VTK)\n");
        fprintf(stderr, "  <base>_compare.png  - side-by-side comparison\n");
        return 1;
    }
    const char *base = argv[1];
    int Width = (argc >= 4) ? atoi(argv[2]) : 800;
    int Height = (argc >= 4) ? atoi(argv[3]) : 600;

    OSMesaContext ctx = OSMesaCreateContextExt(OSMESA_RGBA, 0, 0, 0, NULL);
    if (!ctx) {
        fprintf(stderr, "OSMesaCreateContext failed!\n");
        return 1;
    }

    /* Allocate buffer */
    unsigned char *buffer = (unsigned char *)calloc((size_t)Width * (size_t)Height, 4);
    if (!buffer) {
        fprintf(stderr, "Alloc image buffer failed!\n");
        OSMesaDestroyContext(ctx);
        return 1;
    }
    if (!OSMesaMakeCurrent(ctx, buffer, GL_UNSIGNED_BYTE, Width, Height)) {
        fprintf(stderr, "OSMesaMakeCurrent failed!\n");
        free(buffer);
        OSMesaDestroyContext(ctx);
        return 1;
    }

    /* Avoid the need to flip pixels (origin at top-left) */
    OSMesaPixelStore(OSMESA_Y_UP, 0);

    /* Render aliasing-prone scene WITHOUT FXAA first */
    render_aliasing_scene(Width, Height);

    /* Keep a copy of the pre-FXAA buffer */
    size_t rowBytes = (size_t)Width * 4;
    unsigned char *buffer_pre = (unsigned char *)malloc((size_t)Height * rowBytes);
    if (!buffer_pre) {
        fprintf(stderr, "Alloc pre buffer failed!\n");
        free(buffer);
        OSMesaDestroyContext(ctx);
        return 1;
    }
    memcpy(buffer_pre, buffer, (size_t)Height * rowBytes);

    /* Now enable integrated FXAA and re-render the scene */
    OSMesaFXAAEnable(GL_TRUE);
    
    /* Clear and re-render with FXAA enabled */
    render_aliasing_scene(Width, Height);

    /* Write individual images */
    char fn_nofxaa[512], fn_fxaa[512], fn_compare[512];
    snprintf(fn_nofxaa, sizeof(fn_nofxaa), "%s_nofxaa.png", base);
    snprintf(fn_fxaa,   sizeof(fn_fxaa),   "%s_fxaa.png",   base);
    snprintf(fn_compare,sizeof(fn_compare),"%s_compare.png",base);

    write_png(fn_nofxaa, buffer_pre, Width, Height);
    write_png(fn_fxaa,   buffer,     Width, Height);

    /* Compose side-by-side comparison */
    unsigned char *comp = (unsigned char *)calloc((size_t)Height, (size_t)Width * 8);
    if (comp) {
        for (int y = 0; y < Height; ++y) {
            unsigned char *dst = comp + (size_t)y * (size_t)(Width * 8);
            const unsigned char *srcL = buffer_pre + (size_t)y * rowBytes;
            const unsigned char *srcR = buffer      + (size_t)y * rowBytes;
            memcpy(dst,             srcL, rowBytes);
            memcpy(dst + rowBytes,  srcR, rowBytes);
        }
        write_png(fn_compare, comp, Width * 2, Height);
        free(comp);
    } else {
        fprintf(stderr, "Warning: could not allocate compare buffer; skipping side-by-side image.\n");
    }

    /* Cleanup */
    free(buffer_pre);
    free(buffer);
    OSMesaDestroyContext(ctx);

    fprintf(stdout, "Wrote:\n  %s\n  %s\n  %s\n", fn_nofxaa, fn_fxaa, fn_compare);
    fprintf(stdout, "\nNote: FXAA was applied using OSMesaFXAAEnable() with sRGB color space\n");
    fprintf(stdout, "conversion (matching VTK's approach for improved visual quality).\n");
    return 0;
}
