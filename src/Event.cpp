//
// Created by aviral on 7/22/22.
//
#include "Chip8.h"

void Chip8::OnEvent(SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        closed = true;
    }
}