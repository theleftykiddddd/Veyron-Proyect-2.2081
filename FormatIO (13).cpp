#include "veyron/FormatIO.hpp"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <utility>

namespace veyron {

IoResult exportVpr(const Macro& macro, const std::string& path) {
    std::string reason;
    if (!macro.isValid(&reason)) return {false, "Macro validation failed: " + reason};

    std::ofstream file(path);
    if (!file) return {false, "Cannot open output file."};

    file << "VEYRON_MACRO 1\n"
         << std::quoted(macro.metadata.title) << ' '
         << std::quoted(macro.metadata.author) << '\n'
         << macro.metadata.levelId << ' '
         << std::quoted(macro.metadata.levelName) << ' '
         << std::setprecision(12) << macro.metadata.gameVersion << ' '
         << macro.metadata.tickRate << '\n'
         << macro.inputs.size() << '\n';

    for (const auto& event : macro.inputs) {
        file << event.frame << ' ' << event.button << ' '
             << event.player2 << ' ' << event.down << '\n';
    }

    return file ? IoResult{true, "VPR exported."} : IoResult{false, "Write failed."};
}

IoResult importVpr(const std::string& path, Macro& out) {
    std::ifstream file(path);
    if (!file) return {false, "Cannot open input file."};

    std::string magic;
    int formatVersion = 0;
    file >> magic >> formatVersion;
    if (magic != "VEYRON_MACRO" || formatVersion != 1) {
        return {false, "Unsupported VPR header/version."};
    }

    Macro imported;
    file >> std::quoted(imported.metadata.title) >> std::quoted(imported.metadata.author);
    file >> imported.metadata.levelId >> std::quoted(imported.metadata.levelName)
         >> imported.metadata.gameVersion >> imported.metadata.tickRate;

    std::size_t eventCount = 0;
    file >> eventCount;
    if (!file || eventCount == 0 || eventCount > 5'000'000) {
        return {false, "Invalid or excessive event count."};
    }

    imported.inputs.reserve(eventCount);
    for (std::size_t i = 0; i < eventCount; ++i) {
        InputEvent event;
        file >> event.frame >> event.button >> event.player2 >> event.down;
        if (!file) return {false, "Truncated or malformed event list."};
        imported.inputs.push_back(event);
    }

    std::string reason;
    if (!imported.isValid(&reason)) return {false, "Imported macro failed validation: " + reason};
    out = std::move(imported);
    return {true, "VPR imported."};
}

IoResult importExternal(std::string_view format, const std::string&, Macro&) {
    return {false, "Adapter for '" + std::string(format) +
                   "' is not implemented. Use VPR until a spec-verified adapter is added."};
}

IoResult exportExternal(std::string_view format, const Macro&, const std::string&) {
    return {false, "Adapter for '" + std::string(format) +
                   "' is not implemented. No incompatible file was written."};
}

} // namespace veyron
