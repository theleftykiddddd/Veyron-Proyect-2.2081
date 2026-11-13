#pragma once
#include "Macro.hpp"
#include <string>
#include <string_view>
namespace veyron {
struct IoResult { bool ok=false; std::string message; };
IoResult exportVpr(const Macro&, const std::string& path);
IoResult importVpr(const std::string& path, Macro& out);
IoResult importExternal(std::string_view format, const std::string& path, Macro& out);
IoResult exportExternal(std::string_view format, const Macro&, const std::string& path);
}
