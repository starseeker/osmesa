# FXAA CPU Post-Processing

This directory contains a CPU-based implementation of FXAA (Fast Approximate Anti-Aliasing) for OSMesa rendering.

## Overview

FXAA is a post-processing anti-aliasing technique that smooths jagged edges in rendered images. This implementation is a CPU port of VTK's FXAA shader (vtkFXAAFilterFS.glsl) designed to work with OSMesa's software rendering.

## Files

- `fxaa_cpu.h` - Public API header for FXAA processing
- `fxaa_cpu.c` - CPU implementation of FXAA algorithm
- `postprocess_fxaa.c` - Example integration hook (NOT COMPILED - reference only)
- `CMakeLists.txt` - Build configuration for fxaa_cpu library
- `README.md` - This file
- `VTK_COMPARISON.md` - Comparison with VTK's FXAA implementation

Note: `postprocess_fxaa.c` is example code showing how FXAA could be integrated
directly into OSMesa. It's not compiled as part of the build. For current usage,
apply FXAA manually in your application after rendering (see `osdemo_fxaa` example).

## Usage

The basic usage pattern is:

```c
#include "fxaa_cpu.h"

// Configure FXAA parameters
FXAAParams params = {
    .RelativeContrastThreshold = 0.125f,    // Edge detection threshold (relative to local contrast)
    .HardContrastThreshold = 0.0625f,       // Minimum absolute threshold
    .SubpixelBlendLimit = 0.75f,            // Maximum subpixel blending
    .SubpixelContrastThreshold = 0.25f,     // Subpixel detection threshold
    .EndpointSearchIterations = 12          // Edge endpoint search iterations
};

// Prepare image data
ImageRGBA8 img = {
    .rgba = buffer,          // Pointer to RGBA8 pixel data
    .width = width,
    .height = height,
    .strideBytes = width * 4 // Bytes per row
};

// Apply FXAA (can be in-place)
fxaa_apply_rgba8(&img, &img, &params);
```

## Demo

The `osdemo_fxaa` example demonstrates FXAA on a scene designed to exhibit aliasing:

```bash
./osdemo_fxaa <output_basename> [width height]
```

This generates three images:
- `<basename>_nofxaa.png` - Original render
- `<basename>_fxaa.png` - FXAA filtered render
- `<basename>_compare.png` - Side-by-side comparison

## Algorithm

This implementation follows VTK's FXAA approach:

1. **Edge Detection**: Analyzes local luminance contrast to identify edges
2. **Endpoint Search**: Traces edges to find their endpoints (VTK's improved variant)
3. **Subpixel Anti-Aliasing**: Blends with 3x3 neighborhood for subpixel smoothing
4. **Directional Filtering**: Adjusts samples perpendicular to edge direction

## Performance

The CPU implementation processes the entire image serially. For a typical 800x600 image with the demo scene:
- Approximately 5-6% of pixels are modified
- Edge regions see ~20-25% pixel modifications
- Processing is performed with floating-point calculations for accuracy

## References

- VTK FXAA Shader: https://github.com/Kitware/VTK/blob/5f2e388161fa3bee2d01fe047ab5557e9a541cb2/Rendering/OpenGL2/glsl/vtkFXAAFilterFS.glsl
- Original FXAA by Timothy Lottes (NVIDIA)
