//
// Created by aviral on 7/19/22.
//

#include "Chip8.h"
#include "Window.h"
void Chip8::emulate() {
    // Fetch the next instruction
    const int frameDelay = 1000 / 60;
    SDL_Event Event;
    Uint64 frameStart = SDL_GetTicks64();
    Uint64 frameTime;

    while(SDL_PollEvent(&Event)) {
        OnEvent(&Event);
    }

    fetch_instruction();

    // Decode and Execute the instruction
    decode_instruction();

    // Draw the screen
    draw_graphics();
    //Check for Events

    frameTime = SDL_GetTicks64() - frameStart;
//    if(frameTime < frameDelay) {
//        SDL_Delay(frameDelay - frameTime);
//    }

}