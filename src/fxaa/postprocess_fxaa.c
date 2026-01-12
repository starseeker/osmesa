#include "fxaa_cpu.h"

/* 
 * EXAMPLE INTEGRATION CODE - NOT COMPILED
 * 
 * This is example code showing how FXAA could be integrated directly into OSMesa.
 * It would require:
 * 1. Adding an 'enable_fxaa' field to the OSMesaContext structure
 * 2. Calling this function from osmesa.c after rendering
 * 3. Adding a public API to enable/disable FXAA
 * 
 * For now, users should apply FXAA manually in their application code after
 * rendering, as demonstrated in examples/osdemo_fxaa.c
 */

/* Example integration hook: call after rasterization before client reads buffer */
void osmesa_apply_fxaa_if_enabled(OSMesaContext ctx, uint8_t* rgba, int w, int h, int stride) {
    if (!ctx || !ctx->enable_fxaa) return;

    ImageRGBA8 img = { rgba, w, h, stride };
    FXAAParams params = {
        .RelativeContrastThreshold = 0.125f,
        .HardContrastThreshold = 0.0625f,
        .SubpixelBlendLimit = 0.75f,
        .SubpixelContrastThreshold = 0.25f,
        .EndpointSearchIterations = 12
    };

    /* In-place processing */
    fxaa_apply_rgba8(&img, &img, &params);
}