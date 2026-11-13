# Version compatibility

This source archive is retargeted to:

- **Geometry Dash (Windows):** 2.2081
- **Geode SDK / minimum loader version:** 5.11.2
- **Build target:** Win64

The previous build used Geode v6.0.0-alpha.1 and declared GD 2.2091. That is a different compatibility line. The workflow and `mod.json` now both target the 2.2081 / v5.11.2 line.

Do not change only `gd.win` in `mod.json` while leaving the SDK on v6 alpha. The manifest, build SDK, and actual game installation need to agree. This archive does not contain a precompiled `.geode` file; GitHub Actions must compile the Windows package against the configured SDK.
