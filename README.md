# Veyron Proyect

A Geometry Dash / Geode macro-recording core and frame-window analysis starter.

## Target

| Component | Target |
|---|---|
| Geometry Dash | **2.2081 (Windows)** |
| Geode SDK / loader minimum | **5.11.2** |
| Build platform | Windows x64 (`Win64`) |
| Project version | `v0.1.1` |

The project was retargeted from the previous Geode v6 alpha / GD 2.2091 configuration. See [`docs/VERSION_COMPATIBILITY.md`](docs/VERSION_COMPATIBILITY.md).

## Current implementation status

This is a starter repository, not a finished in-game macro tool. It contains a platform-neutral macro model, recorder state machine, replay event scheduler, native VPR import/export, window-band statistics, pitch-frequency mapping, sample data and core tests.

The Geode integration is still minimal. Input hooks, in-game replay injection, a live HUD/counter, Geode audio playback, real frame-window measurement, and third-party format adapters are not implemented. In particular, the replay scheduler only reports which events are due; it does not inject inputs into the game. The project does not claim working xdbot, Silicate, Eclipse or other third-party macro compatibility.

## Build the Geode mod on GitHub

1. Upload the contents of this folder to a GitHub repository.
2. Push to the `main` branch, or open **Actions** and run **Build Veyron Proyect (GD 2.2081)** manually.
3. Wait for both jobs to complete successfully.
4. Open the workflow run and download `Veyron-Proyect-GD-2.2081-Windows`.
5. The downloaded artifact contains the `.geode` package if the Windows build succeeded.

The workflow uses `geode-sdk/build-geode-mod` with Geode SDK `v5.11.2` and target `Win64`. Do not switch the SDK back to `v6.0.0-alpha.1` for this target.

## Test the platform-neutral core locally

Requires CMake 3.21+ and a C++23 compiler.

```bash
cmake -S . -B build -DVEYRON_STANDALONE_TESTS=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

## Build locally with Geode SDK

Install/configure the Geode SDK v5.11.2 and set `GEODE_SDK` to its source directory. Then configure and build with CMake using the Geode SDK workflow documented by Geode. The SDK is not bundled in this repository.

## Real frame windows

A click's hold duration is not its frame window. A real window is the range of input timing offsets that still produce the same intended outcome. A macro alone usually cannot reveal this. Veyron marks unmeasured windows as unknown until a validated measurement backend exists. Data in `examples/reference_distribution.json` is illustrative, not live level data.

## Macro format support

Native `.vpr` import/export is implemented. GDR/GDR2, SLC (Silicate), CML, tcBot and Eclipse adapters are planned but not implemented. See [`docs/FORMAT_MATRIX.md`](docs/FORMAT_MATRIX.md).

## Roadmap

1. Build and load the minimal mod on the exact GD 2.2081 / Geode 5.11.2 installation.
2. Add Geode input hooks and verify authoritative frame/tick capture.
3. Add safe autosave, session controls and VPR file picker.
4. Implement third-party codecs with fixtures and round-trip tests.
5. Add actual replay input injection and validate timing across refresh/tick rates.
6. Implement controlled timing-variation tests and validated window measurement.
7. Implement movable HUD, live counter, histogram and report export.
8. Add Geode audio integration and sound customization.

Macro playback is for testing/research and must not be presented as a legitimate human completion or submitted as a personal record.
