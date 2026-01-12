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