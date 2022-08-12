//
// Created by aviral on 7/16/22.
//

#include "Window.h"

Window::Window(const char *title, int windowWidth, int windowHeight,
               int textureWidth, int textureHeight) {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(title, 0, 0, windowWidth, windowHeight,
                              SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED );
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_STREAMING, textureWidth,
                                textureHeight);
}

void Window::draw(const void *buffer) {
    if (SDL_UpdateTexture(texture, nullptr, buffer, 256) < 0) {
        std::cout << "SDL_UpdateTexture error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    if (SDL_RenderClear(renderer) < 0) {
        std::cout << "SDL_RenderClear error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    if (SDL_RenderCopy(renderer, texture, nullptr, nullptr) < 0) {
        std::cout << "SDL_RenderCopy error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    SDL_RenderPresent(renderer);
}

Window::~Window() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_Quit();
}