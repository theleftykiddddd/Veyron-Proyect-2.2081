#include <Geode/Geode.hpp>
#include "veyron/WindowAnalyzer.hpp"
using namespace geode::prelude;
$execute {
    const auto bands = veyron::WindowAnalyzer::defaultBands();
    log::info("Veyron Proyect v0.1.1 loaded for Geometry Dash 2.2081. {} analysis bands registered.", bands.size());
    log::warn("Prototype build: in-game input hooks, replay injection, HUD and audio adapters are not enabled yet.");
}
