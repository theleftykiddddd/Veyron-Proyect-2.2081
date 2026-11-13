#include "WindowAnalyzer.hpp"
#include <algorithm>
namespace veyron {
std::vector<WindowBand> WindowAnalyzer::defaultBands() {
    return {{0,1,"0-1F",0xF04B68},{2,2,"2F",0xFFBD70},{3,3,"3F",0xF8FF72},{4,4,"4F",0xF4F4F4},{5,6,"5-6F",0x8BE995},{7,8,"7-8F",0x9CCEFF},{9,12,"9-12F",0x897DEB},{13,16,"13-16F",0xB78BEE},{17,24,"17-24F",0xDB74E8}};
}
std::size_t WindowAnalyzer::findBand(const std::vector<WindowBand>& bands,int frames) {
    for (std::size_t i=0;i<bands.size();++i) if(frames>=bands[i].minFrames && frames<=bands[i].maxFrames) return i;
    return bands.size();
}
WindowStats WindowAnalyzer::summarize(const std::vector<MeasuredClick>& clicks,const std::vector<WindowBand>& bands) {
    WindowStats r; r.bands=bands; r.counts.assign(bands.size(),0); std::int64_t total=0; bool has=false;
    for(const auto& c:clicks) {
        if(c.windowFrames<0) { ++r.unknown; continue; }
        ++r.measured; auto b=findBand(bands,c.windowFrames); if(b<r.counts.size()) ++r.counts[b];
        if(!has) { r.minimumFrames=r.maximumFrames=c.windowFrames; has=true; }
        else { r.minimumFrames=std::min(r.minimumFrames,c.windowFrames); r.maximumFrames=std::max(r.maximumFrames,c.windowFrames); }
        total+=c.windowFrames;
    }
    if(r.measured) r.averageFrames=static_cast<double>(total)/static_cast<double>(r.measured); return r;
}
double WindowAnalyzer::toneFrequencyHz(int w,int min,int max,double low,double high) {
    if(max<=min) return low; double c=std::clamp(static_cast<double>(w),static_cast<double>(min),static_cast<double>(max));
    return low+((c-min)/(max-min))*(high-low);
}
}
