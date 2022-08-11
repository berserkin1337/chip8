//
// Created by aviral on 7/14/22.
//
#include "Window.h"
#include <cstdint>
#include <stack>
#include <string>
#include <vector>
#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

class Chip8 {
    // define the memory of the Chip8 which is 4096 bytes
    uint8_t memory[4096]{0};
    // define the registers of the Chip8 which are 16  8-bit registers
    uint8_t V[16];
    // define the index register of the Chip8 which is 2 bytes. It points to
    // current instruction in memory
    uint16_t I;
    // define the program counter of the Chip8 which is 2 bytes
    uint16_t pc;
    // define the stack of the Chip8 which is 16 bytes
    uint16_t stack[16];
    // define the stack pointer of the Chip8 which is 1 byte
    uint8_t sp;
    // define the delay timer of the Chip8 which is 1 byte
    uint delayTimer;
    // define the sound timer of the Chip8 which is 1 byte
    uint8_t soundTimer;
    // define the keypad of the Chip8 which is 16 bytes
    uint8_t keypad[16];
    // define the graphics of the Chip8 which is 64x32 pixels of black and white
    uint32_t display[64 * 32]{0};
    uint16_t opcode;
    // Define  the window
    Window window = Window("Chip8", 640, 320, 64, 32);

    bool closed;
    // fontset
    unsigned char fontSet[80] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0, 0x20, 0x60, 0x20, 0x20, 0x70, 0xF0, 0x10,
            0xF0, 0x80, 0xF0, 0xF0, 0x10, 0xF0, 0x10, 0xF0, 0x90, 0x90, 0xF0, 0x10,
            0x10, 0xF0, 0x80, 0xF0, 0x10, 0xF0, 0xF0, 0x80, 0xF0, 0x90, 0xF0, 0xF0,
            0x10, 0x20, 0x40, 0x40, 0xF0, 0x90, 0xF0, 0x90, 0xF0, 0xF0, 0x90, 0xF0,
            0x10, 0xF0, 0xF0, 0x90, 0xF0, 0x90, 0x90, 0xE0, 0x90, 0xE0, 0x90, 0xE0,
            0xF0, 0x80, 0x80, 0x80, 0xF0, 0xE0, 0x90, 0x90, 0x90, 0xE0, 0xF0, 0x80,
            0xF0, 0x80, 0xF0, 0xF0, 0x80, 0xF0, 0x80, 0x80};
    void OnEvent(SDL_Event *event);

public:
    // define the constructor of the Chip8
    Chip8();
    // define the function to load the game
    void load(const std::string &data);
    // define the function to emulate the Chip8
    void emulate();
    // define the function to decrement the delay timer
    void decrement_delay_timer();
    // define the function to decrement the sound timer
    void decrement_sound_timer();
    // fetch the instruction pointed to by the program counter
    void fetch_instruction();
    // decode the instruction
    void decode_instruction();
    // draw the graphics
    void draw_graphics();
    bool is_running();
};

#endif// CHIP8_CHIP8_H
