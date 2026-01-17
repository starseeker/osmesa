/*
 * Port of VTK's vtkFXAAFilterFS.glsl to OSMesa.
 *
 * SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
 * SPDX-License-Identifier: BSD-3-Clause
 * https://github.com/Kitware/VTK/blob/master/Rendering/OpenGL2/glsl/vtkFXAAFilterFS.glsl
 *
 * CPU FXAA Post-Process (VTK endpoint search variant only)
 *
 * Endpoint search follows the higher-quality VTK algorithm (better single-pixel line handling).
 */

#include "fxaa_cpu.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef FXAA_CLAMP
#define FXAA_CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))
#endif

typedef struct { float x, y; } vec2;

static inline float luminosity(float r, float g, float b) {
    return 0.299f * r + 0.587f * g + 0.114f * b;
}

static inline void load_rgb_u8(const uint8_t* p, float* r, float* g, float* b) {
    *r = p[0] / 255.0f;
    *g = p[1] / 255.0f;
    *b = p[2] / 255.0f;
}

static inline void store_rgb_u8(uint8_t* p, float r, float g, float b) {
    p[0] = (uint8_t)FXAA_CLAMP(lroundf(r * 255.0f), 0, 255);
    p[1] = (uint8_t)FXAA_CLAMP(lroundf(g * 255.0f), 0, 255);
    p[2] = (uint8_t)FXAA_CLAMP(lroundf(b * 255.0f), 0, 255);
}

static inline uint8_t load_a_u8(const uint8_t* p) { return p[3]; }
static inline void store_a_u8(uint8_t* p, uint8_t a) { p[3] = a; }

/* Bilinear sample: normalized coords [0,1] with clamp-to-edge */
static void sample_bilinear_rgb(const ImageRGBA8* img, float u, float v, float* r, float* g, float* b) {
    float x = FXAA_CLAMP(u, 0.0f, 1.0f) * (float)(img->width  - 1);
    float y = FXAA_CLAMP(v, 0.0f, 1.0f) * (float)(img->height - 1);
    int x0 = (int)floorf(x);
    int y0 = (int)floorf(y);
    int x1 = FXAA_CLAMP(x0 + 1, 0, img->width  - 1);
    int y1 = FXAA_CLAMP(y0 + 1, 0, img->height - 1);
    float tx = x - (float)x0;
    float ty = y - (float)y0;

    const uint8_t* p00 = img->rgba + y0 * img->strideBytes + x0 * 4;
    const uint8_t* p10 = img->rgba + y0 * img->strideBytes + x1 * 4;
    const uint8_t* p01 = img->rgba + y1 * img->strideBytes + x0 * 4;
    const uint8_t* p11 = img->rgba + y1 * img->strideBytes + x1 * 4;

    float r00, g00, b00, r10, g10, b10, r01, g01, b01, r11, g11, b11;
    load_rgb_u8(p00, &r00, &g00, &b00);
    load_rgb_u8(p10, &r10, &g10, &b10);
    load_rgb_u8(p01, &r01, &g01, &b01);
    load_rgb_u8(p11, &r11, &g11, &b11);

    float r0 = r00 + tx * (r10 - r00);
    float g0 = g00 + tx * (g10 - g00);
    float b0 = b00 + tx * (b10 - b00);

    float r1 = r01 + tx * (r11 - r01);
    float g1 = g01 + tx * (g11 - g01);
    float b1 = b01 + tx * (b11 - b01);

    *r = r0 + ty * (r1 - r0);
    *g = g0 + ty * (g1 - g0);
    *b = b0 + ty * (b1 - b0);
}

/* Nearest sample at integer offsets for 3x3 neighborhood */
static void sample_nearest_rgb(const ImageRGBA8* img, int ix, int iy, float* r, float* g, float* b) {
    ix = FXAA_CLAMP(ix, 0, img->width  - 1);
    iy = FXAA_CLAMP(iy, 0, img->height - 1);
    const uint8_t* p = img->rgba + iy * img->strideBytes + ix * 4;
    load_rgb_u8(p, r, g, b);
}

/* Endpoint search (VTK variant) — better single-pixel line handling */
static int vtkEndpointSearchCPU(
	const ImageRGBA8* img,
	vec2 posC, float lumC, float lumHC, float lengthSign, vec2 tcPixel,
	int horzSpan, int maxIters, vec2* outPosEdgeAA
	) {
    vec2 posHC = posC;
    vec2 edgeDir = (vec2){0.f, 0.f};
    if (horzSpan) {
	posHC.y += lengthSign;
	edgeDir.x = tcPixel.x;
    } else {
	posHC.x += lengthSign;
	edgeDir.y = tcPixel.y;
    }

    float lumHCN = lumHC, lumHCP = lumHC, lumCN = lumC, lumCP = lumC;
    int doneN = 0, doneP = 0;
    vec2 posHCN = (vec2){ posHC.x - edgeDir.x, posHC.y - edgeDir.y };
    vec2 posHCP = (vec2){ posHC.x + edgeDir.x, posHC.y + edgeDir.y };
    vec2 posCN  = (vec2){ posC.x  - edgeDir.x, posC.y  - edgeDir.y };
    vec2 posCP  = (vec2){ posC.x  + edgeDir.x, posC.y  + edgeDir.y };

    for (int i = 0; i < maxIters; ++i) {
	if (!doneN) {
	    float r,g,b;
	    sample_bilinear_rgb(img, posHCN.x, posHCN.y, &r,&g,&b);
	    lumHCN = luminosity(r,g,b);
	    sample_bilinear_rgb(img, posCN.x, posCN.y, &r,&g,&b);
	    lumCN = luminosity(r,g,b);
	}
	if (!doneP) {
	    float r,g,b;
	    sample_bilinear_rgb(img, posHCP.x, posHCP.y, &r,&g,&b);
	    lumHCP = luminosity(r,g,b);
	    sample_bilinear_rgb(img, posCP.x, posCP.y, &r,&g,&b);
	    lumCP = luminosity(r,g,b);
	}
	doneN = doneN || fabsf(lumHCN - lumHC) > fabsf(lumHCN - lumC)
	    || fabsf(lumCN  - lumC)  > fabsf(lumCN  - lumHC);
	doneP = doneP || fabsf(lumHCP - lumHC) > fabsf(lumHCP - lumC)
	    || fabsf(lumCP  - lumC)  > fabsf(lumCP  - lumHC);
	if (doneN && doneP) break;
	if (!doneN) { posHCN.x -= edgeDir.x; posHCN.y -= edgeDir.y; posCN.x -= edgeDir.x; posCN.y -= edgeDir.y; }
	if (!doneP) { posHCP.x += edgeDir.x; posHCP.y += edgeDir.y; posCP.x += edgeDir.x; posCP.y += edgeDir.y; }
    }

    float dstN, dstP;
    if (horzSpan) { dstN = posC.x - posCN.x; dstP = posCP.x - posC.x; }
    else { dstN = posC.y - posCN.y; dstP = posCP.y - posC.y; }

    int nearestEndpointIsN = dstN < dstP;
    float dst = fminf(dstN, dstP);
    float lumCNear = nearestEndpointIsN ? lumCN : lumCP;

    int needEdgeAA = fabsf(lumCNear - lumHC) < fabsf(lumCNear - lumC);

    float invNegSpanLength = -1.f / (dstN + dstP);
    float pixelOffset = dst * invNegSpanLength + 0.5f;

    *outPosEdgeAA = posC;
    if (horzSpan) outPosEdgeAA->y += pixelOffset * lengthSign;
    else          outPosEdgeAA->x += pixelOffset * lengthSign;

    return needEdgeAA ? 1 : 0;
}

void fxaa_apply_rgba8(const ImageRGBA8* in, ImageRGBA8* out, const FXAAParams* p) {
    // If out == in, use a temp buffer to avoid read/write hazards.
    uint8_t* temp = NULL;
    ImageRGBA8 dst = *out;

    int inPlace = (in->rgba == out->rgba);
    if (inPlace) {
	temp = (uint8_t*)malloc((size_t)in->strideBytes * (size_t)in->height);
	if (!temp) return;
	dst.rgba = temp;
	dst.width = in->width;
	dst.height = in->height;
	dst.strideBytes = in->strideBytes;
    }

    const float tcPixelX = 1.0f / (float)in->width;
    const float tcPixelY = 1.0f / (float)in->height;
    const vec2 tcPixel = { tcPixelX, tcPixelY };

    for (int y = 0; y < in->height; ++y) {
	for (int x = 0; x < in->width; ++x) {
	    vec2 tcC = { (float)x * tcPixelX, (float)y * tcPixelY };

	    int xW = FXAA_CLAMP(x - 1, 0, in->width - 1);
	    int xE = FXAA_CLAMP(x + 1, 0, in->width - 1);
	    int yN = FXAA_CLAMP(y - 1, 0, in->height - 1);
	    int yS = FXAA_CLAMP(y + 1, 0, in->height - 1);

	    const uint8_t* pC = in->rgba + y * in->strideBytes + x * 4;
	    float rC,gC,bC; load_rgb_u8(pC, &rC,&gC,&bC);
	    uint8_t aC = load_a_u8(pC);

	    float rN,gN,bN, rS,gS,bS, rW,gW,bW, rE,gE,bE;
	    sample_nearest_rgb(in, x,  yN, &rN,&gN,&bN);
	    sample_nearest_rgb(in, x,  yS, &rS,&gS,&bS);
	    sample_nearest_rgb(in, xW, y,  &rW,&gW,&bW);
	    sample_nearest_rgb(in, xE, y,  &rE,&gE,&bE);

	    float rNE,gNE,bNE, rSE,gSE,bSE, rNW,gNW,bNW, rSW,gSW,bSW;
	    sample_nearest_rgb(in, xE, yN, &rNE,&gNE,&bNE);
	    sample_nearest_rgb(in, xE, yS, &rSE,&gSE,&bSE);
	    sample_nearest_rgb(in, xW, yN, &rNW,&gNW,&bNW);
	    sample_nearest_rgb(in, xW, yS, &rSW,&gSW,&bSW);

	    float lumC = luminosity(rC,gC,bC);
	    float lumN = luminosity(rN,gN,bN);
	    float lumS = luminosity(rS,gS,bS);
	    float lumW = luminosity(rW,gW,bW);
	    float lumE = luminosity(rE,gE,bE);
	    float lumNE = luminosity(rNE,gNE,bNE);
	    float lumSE = luminosity(rSE,gSE,bSE);
	    float lumNW = luminosity(rNW,gNW,bNW);
	    float lumSW = luminosity(rSW,gSW,bSW);

	    float lumMin = fminf(lumC, fminf(fminf(lumN, lumS), fminf(lumW, lumE)));
	    float lumMax = fmaxf(lumC, fmaxf(fmaxf(lumN, lumS), fmaxf(lumW, lumE)));
	    float lumRange = lumMax - lumMin;
	    float lumThresh = fmaxf(p->HardContrastThreshold,
		    p->RelativeContrastThreshold * lumMax);

	    float outR = rC, outG = gC, outB = bC;

	    if (lumRange >= lumThresh) {
		float lumNS   = lumN + lumS;
		float lumWE   = lumW + lumE;
		float lumNSWE = lumNS + lumWE;
		float lumNWNE = lumNW + lumNE;
		float lumSWSE = lumSW + lumSE;
		float lumNWSW = lumNW + lumSW;
		float lumNESE = lumNE + lumSE;

		float lumAveNSWE = 0.25f * lumNSWE;
		float lumSubRange = fabsf(lumAveNSWE - lumC);
		float blendSub = fmaxf(0.f, (lumSubRange / lumRange) - p->SubpixelContrastThreshold);
		blendSub = fminf(p->SubpixelBlendLimit,
			blendSub * (1.f / (1.f - p->SubpixelContrastThreshold)));

		float edgeVertRow1 = fabsf(-2.f * lumN + lumNWNE);
		float edgeVertRow2 = fabsf(-2.f * lumC + lumWE);
		float edgeVertRow3 = fabsf(-2.f * lumS + lumSWSE);
		float edgeVert = ((2.f * edgeVertRow2 + edgeVertRow1) + edgeVertRow3) / 12.f;

		float edgeHorzCol1 = fabsf(-2.f * lumW + lumNWSW);
		float edgeHorzCol2 = fabsf(-2.f * lumC + lumNS);
		float edgeHorzCol3 = fabsf(-2.f * lumE + lumNESE);
		float edgeHorz = ((2.f * edgeHorzCol2 + edgeHorzCol1) + edgeHorzCol3) / 12.f;

		int horzSpan = edgeHorz >= edgeVert;

		float lumHC1, lumHC2;
		float lengthSign;
		if (horzSpan) {
		    lumHC1 = lumN; lumHC2 = lumS; lengthSign = -tcPixelY; // assume N
		} else {
		    lumHC1 = lumW; lumHC2 = lumE; lengthSign = -tcPixelX; // assume W
		}
		float lumHC = lumHC1;
		if (fabsf(lumC - lumHC1) < fabsf(lumC - lumHC2)) {
		    lumHC = lumHC2;
		    lengthSign = -lengthSign;
		}

		vec2 posEdgeAA;
		int needEdgeAA = vtkEndpointSearchCPU(in, tcC, lumC, lumHC, lengthSign, tcPixel, horzSpan,
			p->EndpointSearchIterations, &posEdgeAA);

		float rEdge,gEdge,bEdge;
		if (needEdgeAA) {
		    sample_bilinear_rgb(in, posEdgeAA.x, posEdgeAA.y, &rEdge,&gEdge,&bEdge);
		} else {
		    rEdge = rC; gEdge = gC; bEdge = bC;
		}

		float rSub = (1.f/9.f) * (rNW + rN + rNE + rW + rC + rE + rSW + rS + rSE);
		float gSub = (1.f/9.f) * (gNW + gN + gNE + gW + gC + gE + gSW + gS + gSE);
		float bSub = (1.f/9.f) * (bNW + bN + bNE + bW + bC + bE + bSW + bS + bSE);

		outR = rEdge + blendSub * (rSub - rEdge);
		outG = gEdge + blendSub * (gSub - gEdge);
		outB = bEdge + blendSub * (bSub - bEdge);
	    }

	    uint8_t* pOut = dst.rgba + y * dst.strideBytes + x * 4;
	    store_rgb_u8(pOut, outR, outG, outB);
	    store_a_u8(pOut, aC);
	}
    }

    if (inPlace) {
	memcpy(out->rgba, dst.rgba, (size_t)dst.strideBytes * (size_t)dst.height);
	free(temp);
    }
}

/* sRGB <-> Linear RGB conversion functions */
static inline float linear_to_srgb(float linear) {
    if (linear <= 0.0031308f)
	return linear * 12.92f;
    else
	return 1.055f * powf(linear, 1.0f/2.4f) - 0.055f;
}

static inline float srgb_to_linear(float srgb) {
    if (srgb <= 0.04045f)
	return srgb / 12.92f;
    else
	return powf((srgb + 0.055f) / 1.055f, 2.4f);
}

void fxaa_apply_rgba8_srgb(const ImageRGBA8* in, ImageRGBA8* out, const FXAAParams* p) {
    /* 
     * Allocate temporary buffers for sRGB conversion.
     * 
     * NOTE: This implementation uses two temporary buffers for clarity and correctness.
     * Future optimization: Could reduce memory overhead by:
     *   1. Processing in tiles to reduce buffer size
     *   2. Combining conversion passes where possible
     *   3. Using SIMD for faster conversion
     * Current approach prioritizes correctness and code clarity.
     */
    size_t bufferSize = (size_t)in->strideBytes * (size_t)in->height;
    uint8_t* srgbBuffer = (uint8_t*)malloc(bufferSize);
    if (!srgbBuffer) return;

    /* Convert linear RGB to sRGB */
    for (int y = 0; y < in->height; ++y) {
	for (int x = 0; x < in->width; ++x) {
	    const uint8_t* pIn = in->rgba + y * in->strideBytes + x * 4;
	    uint8_t* pSrgb = srgbBuffer + y * in->strideBytes + x * 4;

	    float r = pIn[0] / 255.0f;
	    float g = pIn[1] / 255.0f;
	    float b = pIn[2] / 255.0f;

	    r = linear_to_srgb(r);
	    g = linear_to_srgb(g);
	    b = linear_to_srgb(b);

	    pSrgb[0] = (uint8_t)FXAA_CLAMP(lroundf(r * 255.0f), 0, 255);
	    pSrgb[1] = (uint8_t)FXAA_CLAMP(lroundf(g * 255.0f), 0, 255);
	    pSrgb[2] = (uint8_t)FXAA_CLAMP(lroundf(b * 255.0f), 0, 255);
	    pSrgb[3] = pIn[3]; /* Preserve alpha */
	}
    }

    /* Apply FXAA in sRGB space */
    ImageRGBA8 srgbImg = { srgbBuffer, in->width, in->height, in->strideBytes };
    uint8_t* fxaaBuffer = (uint8_t*)malloc(bufferSize);
    if (!fxaaBuffer) {
	free(srgbBuffer);
	return;
    }
    ImageRGBA8 fxaaImg = { fxaaBuffer, in->width, in->height, in->strideBytes };

    fxaa_apply_rgba8(&srgbImg, &fxaaImg, p);

    /* Convert sRGB back to linear RGB */
    for (int y = 0; y < in->height; ++y) {
	for (int x = 0; x < in->width; ++x) {
	    const uint8_t* pSrgb = fxaaBuffer + y * in->strideBytes + x * 4;
	    uint8_t* pOut = out->rgba + y * out->strideBytes + x * 4;

	    float r = pSrgb[0] / 255.0f;
	    float g = pSrgb[1] / 255.0f;
	    float b = pSrgb[2] / 255.0f;

	    r = srgb_to_linear(r);
	    g = srgb_to_linear(g);
	    b = srgb_to_linear(b);

	    pOut[0] = (uint8_t)FXAA_CLAMP(lroundf(r * 255.0f), 0, 255);
	    pOut[1] = (uint8_t)FXAA_CLAMP(lroundf(g * 255.0f), 0, 255);
	    pOut[2] = (uint8_t)FXAA_CLAMP(lroundf(b * 255.0f), 0, 255);
	    pOut[3] = pSrgb[3]; /* Preserve alpha */
	}
    }

    free(srgbBuffer);
    free(fxaaBuffer);
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
