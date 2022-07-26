#include "Chip8.h"
#include <iostream>

Chip8::Chip8() {
    // initialize the memory of the Chip8 which is 4096 bytes
    for (auto & i : memory) {
        i =  0;
    }
    // initialize the registers of the Chip8 which are 16  8-bit registers
    for (unsigned char & i : V) {
        i = 0;
    }
    // initialize the index register of the Chip8 which is 2 bytes. It points to current instruction in memory
    I = 0;
    // initialize the program counter of the Chip8 which is 2 bytes
    pc = 0x200;
    // initialize the stack of the Chip8 which is 16 bytes
    // initialize the stack pointer of the Chip8 which is 1 byte
    sp = 0;
    // initialize the delay timer of the Chip8 which is 1 byte
    stack[sp] = 0;
    delay_timer = 0;
    // initialize the sound timer of the Chip8 which is 1 byte
    sound_timer = 0;
    // initialize the keypad of the Chip8 which is 16 bytes
    for (unsigned char & i : keypad) {
        i = 0;
    }
    // initialize the graphics of the Chip8 which is 64x32 pixels of black and white
    for(auto pixel: display) {
        pixel = 0;
    }
    // store the font between address 0x50 and 0x9F in memory
    for (int i = 0; i < 80; i++) {
        memory[i + 0x50] = fontSet[i];
    }
    // initialize the opcode of the Chip8 which is 2 bytes
    opcode = 0;
}

bool Chip8::is_running() {
    return !closed;
}
