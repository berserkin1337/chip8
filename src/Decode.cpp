//
// Created by aviral on 7/19/22.
//
#include "Chip8.h"
#include <random>

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
                    //                    std::cout << "0x00EE: Returns from a subroutine" <<
                    //                    std::endl;
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
        case 0x2000:
            stack[sp] = pc;
            sp += 1;
            pc = opcode & 0x0FFF;
        case 0x3000:
            // 0x3XNN
            if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)) {
                pc += 2;
            }
        case 0x4000:
            // 0x4XNN
            if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)) {
                pc += 2;
            }
        case 0x5000:
            // 5XY0
            if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4]) {
                pc += 2;
            }

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
        case 0x8000:
            switch (opcode & 0x000F) {
                case 0x0000:
                    // Set Vx to Vy
                    V[(opcode & 0x0F00u) >> 8] = V[(opcode & 0x00F0) >> 4];
                    break;
                case 0x0001:
                    V[(opcode & 0x0F00) >> 8] =
                            V[(opcode & 0x0F00) >> 8] | V[(opcode & 0x00F0) >> 4];
                    break;
                case 0x0002:
                    V[(opcode & 0x0F00) >> 8] =
                            V[(opcode & 0x0F00) >> 8] & V[(opcode & 0x00F0) >> 4];
                    break;
                case 0x0003:
                    V[(opcode & 0x0F00) >> 8] =
                            V[(opcode & 0x0F00) >> 8] ^ V[(opcode & 0x00F0) >> 4];
                    break;
                case 0x0004:
                    if (V[(opcode & 0x0F00) >> 8] + V[(opcode & 0x00F0) >> 4] > 0xFF) {
                        V[0xF] = 1;
                    } else {
                        V[0xF] = 0;
                    }
                    V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
                    break;
                case 0x0005:
                    if (V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4]) {
                        V[0xF] = 1;
                    } else {
                        V[0xF] = 0;
                    }
                    V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
                    break;
                case 0x0007:
                    if (V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4]) {
                        V[0xF] = 0;
                    } else {
                        V[0xF] = 1;
                    }
                    V[(opcode & 0x0F00) >> 8] =
                            V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
                    break;
                case 0x0006:
                    // Set VF to 1 if the bit that was shifted out was 1, or 0 if it was 0
                    V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x1;
                    // shift the value of Vx right by one.
                    V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x0F00) >> 8] >> 1;
                case 0x000E:
                    uint8_t Vx = (opcode & 0x0F00) >> 8;
                    V[0xF] = (V[Vx] & 0x80) >> 7;
                    V[Vx] <<= 1;
                    break;
            }
        case 0xA000:
            // Set I to NNN
            //            std::cout<<"0xANNN: Set I to NNN"<<std::endl;
            I = opcode & 0x0FFF;
            break;
        case 0xB000:
            // Jump to address NNN + V0
            //            std::cout<<"0xBNNN: Jump to address NNN + V0"<<std::endl;
            pc = (opcode & 0x0FFF) + V[0];
            break;
        case 0xC000: {
            uint8_t Vx = (opcode & 0x0F00) >> 8;
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 255);
            V[Vx] = dist6(rng) & (opcode & 0x00FF);
        }
            break;
        case 0xD000: { //            std::cout << "DXYN\n";
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
        }
            break;
        case 0xE000:
            switch (opcode & 0x00FF) {
                case 0x009E:
                    // Skip next instruction if key with the value of Vx is pressed
                    //                    std::cout<<"0xEx9E: Skip next instruction if key with the value of Vx is pressed"<<std::endl;
                    if (keypad[V[(opcode & 0x0F00) >> 8]]) {
                        pc += 2;
                    }
                    break;
                case 0x00A1:
                    // Skip next instruction if key with the value of Vx is not pressed
                    //                    std::cout<<"0xExA1: Skip next instruction if key with the value of Vx is not pressed"<<std::endl;
                    if (!keypad[V[(opcode & 0x0F00u) >> 8u]]) {
                        pc += 2;
                    }
                    break;

            }
        case 0xF000:
            switch (opcode & 0x00FF) {
                case 0x0007:
                    // Set Vx to value of delay timer
//                    std::cout<<"0xFX07: Set Vx to value of delay timer"<<std::endl;
                    V[(opcode & 0x0F00) >> 8] = delay_timer;
                    break;
                case 0x0015:
                    // Set delay timer to Vx
//                    std::cout<<"0xFX15: Set delay timer to Vx"<<std::endl;
                    delay_timer = V[(opcode & 0x0F00) >> 8];
                    break;
                case 0x0018:
                    // Set sound timer to Vx
                    sound_timer = V[(opcode & 0x0F00) >> 8];
                    break;
                case 0x001E:
                    // Set I to I + Vx
                    I += V[(opcode & 0x0F00) >> 8];
                    break;
                case 0x000A: {
                    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
                    bool found = false;
                    // Wait for a key press, store the value of the key in Vx
                    for (int i = 0; i < 16; ++i) {
                        if (keypad[i]) {
                            V[Vx] = i;
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        pc -= 2;
                    }
                }
                    break;
                case 0x0029:
                    //set index register to  the address of the hexadecimal character in VX
                    I = V[(opcode & 0x0F00) >> 8] * 5 + 0x50;
                    break;
                case 0x0033: {
                    uint8_t value = V[(opcode & 0x0F00u) >> 8u];
                    memory[I + 2] = value % 10;
                    value /= 10;
                    memory[I + 1] = value % 10;
                    value /= 10;
                    memory[I] = value % 10;
                }
                case 0x0055:
                    // Store registers V0 to Vx in memory starting at location I
                    for (int i = 0; i <= ((opcode & 0x0F00u) >> 8u); ++i) {
                        memory[I + i] = V[i];
                    }
                    break;
                case 0x0065:
                    // Read registers V0 to Vx from memory starting at location I
                    for (int i = 0; i <= ((opcode & 0x0F00u) >> 8u); ++i) {
                        V[i] = memory[I + i];
                    }
                    break;
            }
    }
}
