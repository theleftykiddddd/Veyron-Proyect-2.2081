#include <Geode/Geode.hpp>
#include "veyron/WindowAnalyzer.hpp"

using namespace geode::prelude;

$execute {
    const auto bands = veyron::WindowAnalyzer::defaultBands();
    log::info("Veyron Proyect v0.1.1 loaded for Geometry Dash 2.2081. {} analysis bands registered.", bands.size());
    log::warn("Veyron is currently a starter build: in-game input hooks, replay injection, HUD rendering, and audio playback are not implemented yet.");
}
