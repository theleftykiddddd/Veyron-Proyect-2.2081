#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace veyron {
struct InputEvent { std::uint64_t frame=0; int button=0; bool player2=false; bool down=false; };
struct MacroMetadata {
    std::string title; std::string author; std::uint32_t levelId=0; std::string levelName;
    double gameVersion=2.2081; double tickRate=240.0; std::string sourceFormat="veyron-json";
};
struct Macro {
    MacroMetadata metadata; std::vector<InputEvent> inputs;
    void sortByFrameStable();
    [[nodiscard]] bool isValid(std::string* reason=nullptr) const;
};
}
