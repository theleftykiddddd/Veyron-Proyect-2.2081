#pragma once

#include "veyron/Macro.hpp"
#include <string>
#include <string_view>

namespace veyron {

struct IoResult {
    bool ok = false;
    std::string message;
};

// VPR is Veyron's native line-oriented format, not a third-party format.
IoResult exportVpr(const Macro& macro, const std::string& path);
IoResult importVpr(const std::string& path, Macro& out);

// External adapters stay explicit until real format specs and fixtures are tested.
IoResult importExternal(std::string_view format, const std::string& path, Macro& out);
IoResult exportExternal(std::string_view format, const Macro& macro, const std::string& path);

} // namespace veyron
