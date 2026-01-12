# OSMesa FXAA Demonstration

This example renders aliasing-prone 2D geometry (thin high-contrast edges, rotated bars, single-pixel lines, and a fine checker grid) and applies a CPU FXAA filter ported from VTK's `vtkFXAAFilterFS.glsl`. It writes three images:

- `<base>_nofxaa.png` – original render (no post-process)
- `<base>_fxaa.png` – FXAA post-processed render
- `<base>_compare.png` – side-by-side (left: no FXAA, right: FXAA)

## Build

Assuming `fxaa_cpu.h/c` and `svpng.h` are available and OSMesa is installed:

```sh
cc -O2 -I. -I./OSMesa -o osdemo_fxaa examples/osdemo_fxaa.c src/fxaa_cpu.c -lOSMesa -lm
```

Adjust include/library paths as needed.

## Run

```sh
./osdemo_fxaa output_base 800 600
```

Produces:
- `output_base_nofxaa.png`
- `output_base_fxaa.png`
- `output_base_compare.png`

## Notes

- FXAA parameters (defaults shown below) match typical VTK usage and favor visible edge smoothing while preserving detail:
  - RelativeContrastThreshold: `0.125`
  - HardContrastThreshold: `0.0625`
  - SubpixelBlendLimit: `0.75`
  - SubpixelContrastThreshold: `0.25`
  - EndpointSearchIterations: `12`

- The filter uses the VTK endpoint search variant (better for single-pixel lines and thin wireframes) and runs entirely on CPU.

- For even clearer aliasing, reduce the image size (e.g., `640x360`) or increase the density of grid/line patterns.
