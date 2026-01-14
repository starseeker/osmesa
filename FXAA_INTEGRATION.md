# FXAA Integration for OSMesa

## Overview

FXAA (Fast Approximate Anti-Aliasing) has been integrated into OSMesa as a built-in post-processing feature. This integration provides automatic edge smoothing for rendered images with minimal performance impact.

## Features

- **Integrated API**: Enable/disable FXAA with a single function call
- **sRGB Color Space**: Processes images in sRGB color space (matching VTK's approach) for improved visual quality
- **Automatic Application**: FXAA is applied automatically when `glFinish()` is called
- **VTK-Compatible**: Uses the same algorithm and color space handling as VTK's GPU-based FXAA

## API

### OSMesaFXAAEnable

```c
void OSMesaFXAAEnable(GLboolean enable);
```

Enable or disable FXAA post-processing for the current OSMesa context.

**Parameters:**
- `enable`: `GL_TRUE` to enable FXAA, `GL_FALSE` to disable

**Example:**
```c
OSMesaContext ctx = OSMesaCreateContextExt(OSMESA_RGBA, 16, 0, 0, NULL);
OSMesaMakeCurrent(ctx, buffer, GL_UNSIGNED_BYTE, width, height);

/* Enable FXAA */
OSMesaFXAAEnable(GL_TRUE);

/* Render scene */
render_scene();

/* FXAA is automatically applied when glFinish() is called */
glFinish();
```

## Color Space Handling

The implementation converts rendered images through the following pipeline:

1. **Linear RGB** (from OpenGL rendering)
2. **→ sRGB** (via gamma encoding for FXAA processing)
3. **FXAA processing** (in sRGB color space)
4. **→ Linear RGB** (via gamma decoding for final output)

This matches VTK's approach and provides better visual quality than processing in linear space, as FXAA's luminance calculations work better in perceptual color space.

## Limitations

- Currently only works with RGBA 8-bit unsigned byte buffers
- FXAA is applied in-place on the framebuffer
- Uses fixed parameters tuned for general-purpose rendering

## FXAA Parameters

The implementation uses the following parameters (matching VTK defaults):

- **RelativeContrastThreshold**: 0.125
- **HardContrastThreshold**: 0.0625
- **SubpixelBlendLimit**: 0.75
- **SubpixelContrastThreshold**: 0.25
- **EndpointSearchIterations**: 12

These parameters provide a good balance between quality and performance for typical 3D rendering scenarios.

## Demo Programs

### osdemo

The basic demo now supports an optional `-fxaa` flag:

```bash
./osdemo output.png 800 600 -fxaa
```

### osdemo_fxaa

The FXAA demo has been updated to use the integrated FXAA feature and demonstrates the visual difference:

```bash
./osdemo_fxaa comparison 800 600
```

This generates three images:
- `comparison_nofxaa.png`: Original rendering without FXAA
- `comparison_fxaa.png`: Rendering with FXAA applied
- `comparison_compare.png`: Side-by-side comparison

## Technical Details

### Implementation

FXAA is implemented in `osmesa_finish()`, which is called by `glFinish()`. The function:

1. Checks if FXAA is enabled for the context
2. Verifies the buffer format is compatible (RGBA8)
3. Converts the linear RGB buffer to sRGB
4. Applies FXAA using the CPU implementation
5. Converts the result back to linear RGB

### Performance

FXAA is a post-processing effect that runs on the CPU. Performance depends on image resolution:

- 800×600: ~10-20ms on modern CPUs
- 1920×1080: ~40-80ms on modern CPUs

For offline rendering scenarios (the primary use case for OSMesa), this overhead is typically acceptable.

## Comparison with VTK

The implementation closely follows VTK's FXAA shader:
- Same luminance calculation (0.299R + 0.587G + 0.114B)
- Same endpoint search algorithm (high-quality variant)
- Same color space handling (sRGB for processing)
- Same default parameters

The main difference is that VTK runs on GPU while OSMesa runs on CPU, but the visual results should be nearly identical.

## References

- VTK FXAA Shader: https://github.com/Kitware/VTK/blob/master/Rendering/OpenGL2/glsl/vtkFXAAFilterFS.glsl
- NVIDIA FXAA Whitepaper: https://developer.nvidia.com/fxaa
