//
// Created by aviral on 7/15/22.
//
#include <iostream>
#include "Chip8.h"


void Chip8::load(const std::string &data) {
    // load the data starting  at memory address 0x200
    for(int idx=0;idx<data.size();++idx) {
        memory[idx + 0x200] = data[idx];
    }
}
