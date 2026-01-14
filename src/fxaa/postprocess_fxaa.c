/* 
 * FXAA INTEGRATION - NOW FULLY INTEGRATED INTO OSMESA
 * 
 * This example code has been successfully integrated into OSMesa.
 * The functionality is now available through the OSMesaFXAAEnable() API.
 * 
 * Usage:
 *   OSMesaContext ctx = OSMesaCreateContextExt(OSMESA_RGBA, 16, 0, 0, NULL);
 *   OSMesaMakeCurrent(ctx, buffer, GL_UNSIGNED_BYTE, width, height);
 *   OSMesaFXAAEnable(GL_TRUE);  // Enable FXAA
 *   render_scene();
 *   glFinish();  // FXAA is applied automatically
 * 
 * Features:
 * - Integrated into osmesa.c with driver hook in glFinish()
 * - Uses sRGB color space conversion (matching VTK) for better quality
 * - Public API: OSMesaFXAAEnable(GLboolean enable)
 * - Applied automatically when rendering completes
 * 
 * See FXAA_INTEGRATION.md for full documentation.
 * 
 * Original example code preserved below for reference:
 */

#if 0  /* BEGIN NON-COMPILED EXAMPLE CODE */

#include "fxaa_cpu.h"

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

#endif  /* END NON-COMPILED EXAMPLE CODE */