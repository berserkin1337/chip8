//
// Created by aviral on 7/19/22.
//
#include "Chip8.h"

void Chip8::decode_instruction() {
    // Check for 0NNN instruction
    switch (opcode & 0xF000) {
        case 0x0000:
            switch (opcode) {
                case 0x00E0:
                    std::cout << "0x00E0: Clears the screen" << std::endl;
                    // Clear the display
                    for (int i = 0; i < 64 * 32; ++i) {
                        display[i] = false;
                    }
                    break;
                case 0x00EE:
//                    std::cout << "0x00EE: Returns from a subroutine" << std::endl;
                    // Return from a subroutine
                    --sp;
                    pc = stack[sp];
                    break;
            }
            break;
        case 0x1000:
            // Jump to address NNN
//            std::cout<<"0x1NNN: Jump to address NNN"<<std::endl;
            pc = opcode & 0x0FFFu;
            break;
        case 0x6000:
            // Set Vx to NN
//            std::cout<<"0x6xNN: Set Vx to NN"<<std::endl;
            V[(opcode & 0x0F00u) >> 8u] = opcode & 0x00FF;
            break;
        case 0x7000:
            // Add NN to Vx
//            std::cout<<"0x7xNN: Add NN to Vx"<<std::endl;
            V[(opcode & 0x0F00u) >> 8u] += opcode & 0x00FFu;
            break;
        case 0xA000:
            // Set I to NNN
//            std::cout<<"0xANNN: Set I to NNN"<<std::endl;
            I = opcode & 0x0FFF;
            break;
        case 0xD000:
//            std::cout << "DXYN\n";
            uint8_t height = opcode & 0x000Fu;
            uint8_t xPos = V[(opcode & 0x0F00u) >> 8u] % 64;
            uint8_t yPos = V[(opcode & 0x00F0u) >> 4u] % 32;
            V[0xF] = 0;
            for (int row = 0; row < height; ++row) {
                uint8_t spriteByte = memory[I + row];

                for (int col = 0; col < 8; ++col) {
                    uint8_t spritePixel = spriteByte & (0x80u >> col);
                    uint32_t *screenPixel = &display[(yPos + row) * 64 + (xPos + col)];

                    // Sprite pixel is on
                    if (spritePixel) {
                        if (*screenPixel == 0xFFFFFFFF) {
                            V[0xF] = 1;
                        }
                        *screenPixel ^= 0xFFFFFFFF;
                    }
                }
            }
            // Print the display array to stdout
//            for (int i = 0; i < 64 * 32; ++i) {
//                std::cout << display[i];
//                if ((i + 1) % 64 == 0) {
//                    std::cout << std::endl;
//                }
//            }
            break;
    }
}