//
// Created by aviral on 7/16/22.
//

#ifndef CHIP8_WINDOW_H
#define CHIP8_WINDOW_H
#include <SDL.h>
#include <string>
#include <iostream>

class Window {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

public:
    Window(const char* title, int windowWidth, int height, int textureWidth, int textureHeight);
    ~Window();
    //close the window
    void draw(void const* buffer);
};


#endif //CHIP8_WINDOW_H
