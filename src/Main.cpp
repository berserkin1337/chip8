#include "Chip8.h"
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include "cmdline.h"
auto get_frequency(cxxopts::ParseResult &parse_result) {
    using namespace std::literals::chrono_literals;

    auto freq = parse_result["freq"].as<int>();
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Frequency: %d", freq);
    return std::chrono::duration_cast<std::chrono::nanoseconds>(1s) / freq;
}



int main(int argc, char *argv[]) {
    SDL_Log("SDL version: %d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION,
            SDL_PATCHLEVEL);
    // parse the input
    cxxopts::Options options = setup_cmdline();
    cxxopts::ParseResult parse_result = options.parse(argc, argv);
    //check if help was requested
    if (parse_result.count("help")) {
        std::cout << options.help() << std::endl;
        return EXIT_SUCCESS;
    }
    // check if debug was requested
    check_if_debug(parse_result);
    // get the rom path
    std::string filename = get_rom_path(parse_result);
    // get the scale factor
    const int scale = get_scale_factor(parse_result);
    // get the frequency
    const auto freq = get_frequency(parse_result);

    // read data from file
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cout << "Cannot open file " << filename << std::endl;
        return 1;
    }
    const std::string data((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
    // create a Chip8 instance
    Chip8 chip8;
    // load the game
    file.close();
    chip8.load(data);

    // close the file

    //    std::cout << "closing the file" << std::endl;
    // emulate the Chip8
    while (chip8.is_running()) {
        chip8.emulate();
    }
    return 0;
}
