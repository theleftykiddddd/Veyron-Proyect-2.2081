#include "veyron/Macro.hpp"

#include <algorithm>
#include <cmath>

namespace veyron {

void Macro::sortByFrameStable() {
    std::stable_sort(inputs.begin(), inputs.end(), [](const InputEvent& a, const InputEvent& b) {
        return a.frame < b.frame;
    });
}

bool Macro::isValid(std::string* reason) const {
    const auto fail = [reason](const char* message) {
        if (reason) *reason = message;
        return false;
    };

    if (!std::isfinite(metadata.gameVersion) || metadata.gameVersion <= 0.0) {
        return fail("Game version must be a finite value greater than zero.");
    }
    if (!std::isfinite(metadata.tickRate) || metadata.tickRate <= 0.0) {
        return fail("Tick rate must be a finite value greater than zero.");
    }
    if (inputs.empty()) {
        return fail("The macro contains no input events.");
    }
    for (std::size_t i = 1; i < inputs.size(); ++i) {
        if (inputs[i].frame < inputs[i - 1].frame) {
            return fail("Input events are not sorted by frame.");
        }
    }
    if (reason) reason->clear();
    return true;
}

} // namespace veyron
