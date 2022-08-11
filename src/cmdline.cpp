//
// Created by aviral on 8/11/22.
//
#include "cmdline.h"

cxxopts::Options setup_cmdline() {
    using namespace std::literals::string_literals;
    cxxopts::Options options("chip8", "A CHIP-8 emulator");

    options.add_options()("h, help"s, "print help screen"s)(
            "r, rom"s, "rom file to load"s, cxxopts::value<std::string>())(
            "f, freq"s, "Speed of the emulation",
            cxxopts::value<int>()->default_value("500"s))(
            "d, debug"s, "Enable debug strings"s,
            cxxopts::value<bool>())("s,scale"s, "scale factor"s,
                                    cxxopts::value<int>()->default_value("20"));

    return options;
}

void check_if_debug(cxxopts::ParseResult &parse_result) {
    if (parse_result.count("debug")) {
        SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Debug logging enabled");
    }
}

std::string get_rom_path(cxxopts::ParseResult &parse_result) {
    if (parse_result.count("rom")) {
        std::string path = parse_result["rom"].as<std::string>();
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "rom path: %s",
                     path.c_str());
        return path;
    } else {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "No rom file specified");
        exit(EXIT_FAILURE);
    }
}

int get_scale_factor(cxxopts::ParseResult &parse_result) {
    auto scale = parse_result["scale"].as<int>();
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Upscale multiplier: %d", scale);
    return scale;
}
