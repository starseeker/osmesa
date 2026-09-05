/* Directional-light equivalence and throughput probe for flat CAD batches.
 * A constant color-material array forces per-vertex material processing while
 * leaving the lighting equation unchanged.  It is an independent reference
 * for the constant-material fast path, including repeated input normals. */
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "OSMesa/gl.h"
#include "OSMesa/osmesa.h"

enum { ImageSide = 256, DefaultGridSide = 64, MaximumGridSide = 256,
       DefaultFrames = 4, MaximumFrames = 100, VerticesPerCell = 6 };
static const GLfloat frontDiffuse[2][4] = {
    {0.7f, 0.35f, 0.2f, 0.8f}, {0.2f, 0.55f, 0.75f, 0.6f}
};
static const GLfloat backDiffuse[4] = {0.25f, 0.65f, 0.45f, 0.7f};

static int
parse_positive(const char *text, int maximum)
{
    char *end = NULL;
    long value = strtol(text, &end, 10);
    return end && end != text && *end == '\0' && value > 0 &&
        value <= maximum ? (int)value : 0;
}

static void
populate(GLfloat *positions, GLfloat *normals, unsigned grid, int varying)
{
    static const GLfloat corners[VerticesPerCell][2] = {
        {0, 0}, {1, 0}, {1, 1}, {0, 0}, {1, 1}, {0, 1}
    };
    unsigned cell, corner;
    for (cell = 0; cell < grid * grid; ++cell) {
        for (corner = 0; corner < VerticesPerCell; ++corner) {
            const unsigned vertex = cell * VerticesPerCell + corner;
            const unsigned triangle = vertex / 3;
            const unsigned normalIndex = varying ? vertex : triangle;
            /* Alternating winding exercises distinct front/back materials. */
            const unsigned geometricCorner = (cell & 1) ?
                (corner / 3) * 3 + (2 - corner % 3) : corner;
            const GLfloat nx = 0.5f * sinf((GLfloat)normalIndex * 0.17f);
            const GLfloat ny = 0.5f * cosf((GLfloat)normalIndex * 0.23f);
            positions[vertex * 3] =
                1.8f * ((cell % grid) + corners[geometricCorner][0]) / grid - 0.9f;
            positions[vertex * 3 + 1] =
                1.8f * ((cell / grid) + corners[geometricCorner][1]) / grid - 0.9f;
            positions[vertex * 3 + 2] = 0.0f;
            normals[vertex * 3] = nx;
            normals[vertex * 3 + 1] = ny;
            normals[vertex * 3 + 2] =
                sqrtf(1.0f - nx * nx - ny * ny) * ((triangle & 1) ? -1.0f : 1.0f);
        }
    }
}

static void
configure_lights(int twoSided, int lights, int material)
{
    static const GLfloat positions[3][4] = {
        {0.4f, 0.6f, 1.0f, 0.0f}, {-0.7f, 0.2f, 0.5f, 0.0f},
        {0.1f, -0.8f, -0.4f, 0.0f}
    };
    static const GLfloat diffuse[4] = {0.55f, 0.50f, 0.45f, 1.0f};
    static const GLfloat specular[4] = {0.3f, 0.25f, 0.2f, 1.0f};
    static const GLfloat ambient[4] = {0.07f, 0.05f, 0.03f, 1.0f};
    int i;
    glDisable(GL_COLOR_MATERIAL);
    glDisableClientState(GL_COLOR_ARRAY);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, twoSided);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, frontDiffuse[material]);
    glMaterialfv(GL_BACK, GL_DIFFUSE, backDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material ? 17.0f : 48.0f);
    glMaterialf(GL_BACK, GL_SHININESS, material ? 61.0f : 9.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    for (i = 0; i < 3; ++i) {
        glLightfv(GL_LIGHT0 + i, GL_POSITION, positions[i]);
        glLightfv(GL_LIGHT0 + i, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0 + i, GL_SPECULAR, specular);
        if (i < lights)
            glEnable(GL_LIGHT0 + i);
        else
            glDisable(GL_LIGHT0 + i);
    }
    glRotatef(13.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.95f, 0.9f, 1.1f);
}

static double
render(unsigned vertices, unsigned frames)
{
    unsigned frame;
    clock_t start;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices);
    glFinish();
    start = clock();
    for (frame = 0; frame < frames; ++frame) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices);
        glFinish();
    }
    return 1000.0 * (double)(clock() - start) / CLOCKS_PER_SEC / frames;
}

static int
has_visible_pixels(const unsigned char *pixels, size_t bytes)
{
    size_t i;
    for (i = 0; i < bytes; i += 4)
        if (pixels[i] || pixels[i + 1] || pixels[i + 2])
            return 1;
    return 0;
}

static uint32_t
pixel_hash(const unsigned char *pixels, size_t bytes)
{
    uint32_t hash = UINT32_C(2166136261);
    size_t i;
    for (i = 0; i < bytes; ++i)
        hash = (hash ^ pixels[i]) * UINT32_C(16777619);
    return hash;
}

int
main(int argc, char **argv)
{
    const int grid = argc > 1 ? parse_positive(argv[1], MaximumGridSide) : DefaultGridSide;
    const int frames = argc > 2 ? parse_positive(argv[2], MaximumFrames) : DefaultFrames;
    const size_t imageBytes = ImageSide * ImageSide * 4;
    unsigned vertices;
    GLfloat *positions = NULL, *normals = NULL, *colors = NULL;
    unsigned char *pixels = NULL, *reference = NULL;
    OSMesaContext context = NULL;
    int varying, twoSided, lightCase, material, failed = 0;
    if (argc > 3 || !grid || !frames) {
        fprintf(stderr, "usage: %s [grid-side 1..%d] [frames 1..%d]\n",
            argv[0], MaximumGridSide, MaximumFrames);
        return 1;
    }
    vertices = (unsigned)grid * grid * VerticesPerCell;
    positions = (GLfloat *)malloc(vertices * 3 * sizeof(GLfloat));
    normals = (GLfloat *)malloc(vertices * 3 * sizeof(GLfloat));
    colors = (GLfloat *)malloc(vertices * 4 * sizeof(GLfloat));
    pixels = (unsigned char *)calloc(imageBytes, 1);
    reference = (unsigned char *)malloc(imageBytes);
    context = OSMesaCreateContextExt(OSMESA_RGBA, 24, 0, 0, NULL);
    if (!positions || !normals || !colors || !pixels || !reference || !context ||
        !OSMesaMakeCurrent(context, pixels, GL_UNSIGNED_BYTE, ImageSide, ImageSide)) {
        fprintf(stderr, "lighting probe allocation/context failure\n");
        failed = 1;
        goto cleanup;
    }
    glViewport(0, 0, ImageSide, ImageSide);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -2.0, 2.0);
    glEnable(GL_DEPTH_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, positions);
    glNormalPointer(GL_FLOAT, 0, normals);
    for (varying = 0; varying < 2; ++varying) {
        populate(positions, normals, (unsigned)grid, varying);
        for (twoSided = 0; twoSided < 2; ++twoSided) {
            for (lightCase = 0; lightCase < 2; ++lightCase) {
                const int lights = lightCase ? 3 : 1;
                for (material = 0; material < 2; ++material) {
                    unsigned vertex;
                    double fastMs, referenceMs;
                    configure_lights(twoSided, lights, material);
                    fastMs = render(vertices, (unsigned)frames);
                    memcpy(reference, pixels, imageBytes);
                    for (vertex = 0; vertex < vertices; ++vertex)
                        memcpy(&colors[vertex * 4], frontDiffuse[material], 4 * sizeof(GLfloat));
                    glColor4fv(frontDiffuse[material]);
                    glColorMaterial(GL_FRONT, GL_DIFFUSE);
                    glEnable(GL_COLOR_MATERIAL);
                    glEnableClientState(GL_COLOR_ARRAY);
                    glColorPointer(4, GL_FLOAT, 0, colors);
                    referenceMs = render(vertices, (unsigned)frames);
                    if (glGetError() != GL_NO_ERROR || !has_visible_pixels(pixels, imageBytes) ||
                        memcmp(reference, pixels, imageBytes)) {
                        fprintf(stderr, "lighting mismatch varying=%d sides=%d lights=%d material=%d\n",
                            varying, twoSided, lights, material);
                        failed = 1;
                    }
                    printf("varying=%d sides=%d lights=%d material=%d hash=%08x fast_ms=%.3f reference_ms=%.3f\n",
                        varying, twoSided, lights, material, pixel_hash(reference, imageBytes),
                        fastMs, referenceMs);
                }
            }
        }
    }
cleanup:
    if (context)
        OSMesaDestroyContext(context);
    free(reference);
    free(pixels);
    free(colors);
    free(normals);
    free(positions);
    return failed;
}
