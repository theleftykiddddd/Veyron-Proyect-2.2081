#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace veyron {
struct WindowBand { int minFrames=0; int maxFrames=0; std::string label; std::uint32_t colorRGB=0xFFFFFF; };
struct MeasuredClick { std::uint64_t inputFrame=0; int windowFrames=-1; bool player2=false; };
struct WindowStats { std::vector<WindowBand> bands; std::vector<std::uint64_t> counts; std::uint64_t measured=0; std::uint64_t unknown=0; double averageFrames=0.0; int minimumFrames=0; int maximumFrames=0; };
class WindowAnalyzer {
public:
    static std::vector<WindowBand> defaultBands();
    static std::size_t findBand(const std::vector<WindowBand>& bands,int frames);
    static WindowStats summarize(const std::vector<MeasuredClick>& clicks,const std::vector<WindowBand>& bands=defaultBands());
    static double toneFrequencyHz(int windowFrames,int minFrames=1,int maxFrames=24,double lowHz=95.0,double highHz=880.0);
};
}
