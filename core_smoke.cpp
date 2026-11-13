#include "veyron/FormatIO.hpp"
#include "veyron/Macro.hpp"
#include "veyron/Recorder.hpp"
#include "veyron/Replay.hpp"
#include "veyron/WindowAnalyzer.hpp"

#include <cmath>
#include <cstdio>
#include <iostream>
#include <limits>
#include <vector>

static bool check(bool condition, const char* message) {
    if (!condition) std::cerr << "FAILED: " << message << '\n';
    return condition;
}

int main() {
    veyron::MacroMetadata defaultMetadata;
    if (!check(std::abs(defaultMetadata.gameVersion - 2.2081) < 0.000001,
               "default macro game version is 2.2081")) return 1;

    const auto bands = veyron::WindowAnalyzer::defaultBands();
    if (!check(bands.size() == 9 && bands.front().colorRGB == 0xF04B68,
               "default analysis bands")) return 1;
    if (!check(veyron::WindowAnalyzer::findBand(bands, 1) == 0, "1-frame band")) return 1;
    if (!check(veyron::WindowAnalyzer::findBand(bands, 3) == 2, "3-frame band")) return 1;
    if (!check(veyron::WindowAnalyzer::findBand(bands, 24) == 8, "24-frame band")) return 1;

    const std::vector<veyron::MeasuredClick> sample = {
        {10, 1, false}, {20, 3, false}, {30, 8, false}, {40, -1, false}
    };
    const auto stats = veyron::WindowAnalyzer::summarize(sample, bands);
    if (!check(stats.measured == 3 && stats.unknown == 1, "measured and unknown counts")) return 1;
    if (!check(stats.minimumFrames == 1 && stats.maximumFrames == 8, "minimum and maximum")) return 1;
    if (!check(std::abs(stats.averageFrames - 4.0) < 0.001, "average frame window")) return 1;
    if (!check(veyron::WindowAnalyzer::toneFrequencyHz(1) <
               veyron::WindowAnalyzer::toneFrequencyHz(24), "lower window maps to lower pitch")) return 1;

    veyron::Recorder recorder;
    if (!check(recorder.begin(defaultMetadata, 100), "recorder starts")) return 1;
    if (!check(!recorder.begin(defaultMetadata, 200), "recorder cannot start twice")) return 1;
    if (!check(!recorder.record(1, false, true, 99), "recorder rejects frames before start")) return 1;
    if (!check(recorder.record(1, false, true, 105), "recorder stores press")) return 1;
    if (!check(recorder.record(1, false, false, 106), "recorder stores release")) return 1;
    auto captured = recorder.stop();
    if (!check(captured && captured->inputs.size() == 2, "recorder stops with two events")) return 1;
    if (!check(captured->inputs[0].frame == 5 && captured->inputs[1].frame == 6,
               "recorder stores relative frames")) return 1;

    const char* testPath = "veyron-test.vpr";
    if (!check(veyron::exportVpr(*captured, testPath).ok, "VPR export")) return 1;
    veyron::Macro imported;
    if (!check(veyron::importVpr(testPath, imported).ok, "VPR import")) return 1;
    if (!check(imported.inputs.size() == 2 && imported.inputs[1].frame == 6,
               "VPR round trip event data")) return 1;
    if (!check(std::abs(imported.metadata.gameVersion - 2.2081) < 0.000001,
               "VPR round trip target version")) return 1;
    std::remove(testPath);

    veyron::ReplayScheduler replay;
    if (!check(replay.load(*captured), "replay loads valid macro")) return 1;
    replay.start();
    if (!check(replay.advanceTo(5) == 1, "replay advances to first event")) return 1;
    replay.pause();
    if (!check(replay.advanceTo(6) == 0, "paused replay does not advance")) return 1;
    replay.resume();
    if (!check(replay.advanceTo(6) == 1, "resumed replay advances")) return 1;
    if (!check(replay.state() == veyron::ReplayState::Finished, "replay reaches finished state")) return 1;

    veyron::Macro invalid;
    invalid.metadata.tickRate = std::numeric_limits<double>::infinity();
    invalid.inputs.push_back({0, 1, false, true});
    if (!check(!invalid.isValid(), "invalid tick rate is rejected")) return 1;

    std::cout << "All Veyron core checks passed.\n";
    return 0;
}
