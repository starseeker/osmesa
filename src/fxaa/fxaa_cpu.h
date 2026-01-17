/* Port of VTK's vtkFXAAFilterFS.glsl to OSMesa.
 *
 * SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
 * SPDX-License-Identifier: BSD-3-Clause
 * https://github.com/Kitware/VTK/blob/master/Rendering/OpenGL2/glsl/vtkFXAAFilterFS.glsl
 */

#ifndef FXAA_CPU_H
#define FXAA_CPU_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
	float RelativeContrastThreshold;   // e.g. 0.125f
	float HardContrastThreshold;       // e.g. 0.0625f
	float SubpixelBlendLimit;          // e.g. 0.75f
	float SubpixelContrastThreshold;   // e.g. 0.25f
	int   EndpointSearchIterations;    // e.g. 12
    } FXAAParams;

    typedef struct {
	uint8_t* rgba;     // pointer to RGBA8 pixels
	int width;
	int height;
	int strideBytes;   // bytes per row (>= width * 4)
    } ImageRGBA8;

    /* Apply FXAA to an RGBA8 buffer (can be in-place if out == in). */
    void fxaa_apply_rgba8(const ImageRGBA8* in, ImageRGBA8* out, const FXAAParams* p);

    /*
     * Apply FXAA with sRGB color space conversion (matching VTK's approach).
     * Converts linear RGB to sRGB before FXAA, then back to linear after.
     * This improves visual quality by processing in perceptual color space.
     * Can be in-place if out == in.
     */
    void fxaa_apply_rgba8_srgb(const ImageRGBA8* in, ImageRGBA8* out, const FXAAParams* p);

#ifdef __cplusplus
}
#endif

#endif /* FXAA_CPU_H */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8 cino=N-s
 */

