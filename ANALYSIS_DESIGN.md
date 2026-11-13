# Window analysis design

## What is a window?

A click's hold duration is not its frame window. A true window is the range or count of timing offsets around a reference input that still produce the same intended outcome. A macro file by itself usually does not contain that information. Veyron therefore separates:

1. **Observed input spacing**: facts directly present in the macro.
2. **Measured window**: a value supplied by a validated test/simulation backend.
3. **Unknown**: no valid measurement is available.

The starter implements grouping/statistics and pitch mapping for already measured values. It must not label an observed hold length as a real window.

## Default visual bands

The bands use these ranges: 0-1, 2, 3, 4, 5-6, 7-8, 9-12, 13-16, and 17-24 frames. Counts from a reference image are stored separately as illustrative data, not live level measurements.

## Audio

Map lower frame windows to lower frequencies. Proposed defaults: sine wave, 95-880 Hz, 90 ms, 65% master volume. A future Geode audio adapter should add a short cooldown and coalesce same-frame inputs. The core only computes target frequencies.

## HUD

- Current measured window, large and color-coded.
- Total measured clicks and unknown count.
- Counts per band, with optional percentages.
- Current macro frame and recording/playback state.
- Compact mode, movable position, scale, opacity, hide/show hotkey.
- Pause analysis, reset session, export CSV/JSON report.

## Measurement backend

The measurement backend is a future milestone, not a fabricated algorithm. A robust implementation needs controlled replay variants or a validated physics simulation, a definition of “same outcome”, checkpoint/route segmentation, and repeatability checks. It must not infer a true window from a single successful run.
