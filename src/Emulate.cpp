//
// Created by aviral on 7/19/22.
//

#include "Chip8.h"
#include "Window.h"
void Chip8::emulate() {
    // Fetch the next instruction
    const double frameDelay = (1000.0 / 60.0);
    SDL_Event Event;
    uint32_t frameStart = SDL_GetTicks();


    while (SDL_PollEvent(&Event)) {
        OnEvent(&Event);
    }

    fetch_instruction();

    // Decode and Execute the instruction
    decode_instruction();

    // Draw the screen
    draw_graphics();
    // Check for Events
    if (delayTimer > 0) {
        delayTimer--;
    }
    if (soundTimer > 0) {
        soundTimer--;
    }

    int frameTime = SDL_GetTicks() - frameStart;
    std::cout << frameTime - frameDelay << std::endl;
//    if ((double) frameTime < frameDelay) {
//        SDL_Delay(frameDelay - frameTime);
//    }
}


void Chip8::fetch_instruction() {
    // Read the next two bytes from memory in Big Endian and store them in opcode
    opcode = (memory[pc] << 8) | (memory[pc + 1]);
    // Increment the program counter by 2
    pc += 2;
}

void Chip8::draw_graphics() {
    // Draw the screen
    window.draw(display);
}


void Chip8::load(const std::string &data) {
    // load the data starting  at memory address 0x200
    for (int idx = 0; idx < data.size(); ++idx) {
        memory[idx + 0x200] = data[idx];
    }
}
