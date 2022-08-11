//
// Created by aviral on 8/11/22.
//

#ifndef CHIP8_CMDLINE_H
#define CHIP8_CMDLINE_H
#include "cxxopts.h"
#include <SDL_log.h>
#include <SDL_version.h>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>

cxxopts::Options setup_cmdline();
void check_if_debug(cxxopts::ParseResult &parse_result);
std::string get_rom_path(cxxopts::ParseResult &parse_result);
int get_scale_factor(cxxopts::ParseResult &parse_result);
#endif//CHIP8_CMDLINE_H
