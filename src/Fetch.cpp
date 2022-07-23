//
// Created by aviral on 7/19/22.
//
#include "Chip8.h"

void Chip8::fetch_instruction() {
    // Read the next two bytes from memory in Big Endian and store them in opcode
    opcode = (memory[pc] << 8 )| ( memory[pc + 1] ) ;
    // Increment the program counter by 2
    pc += 2;
}