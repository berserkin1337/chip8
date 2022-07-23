//
// Created by aviral on 7/16/22.
//

#include "Window.h"

//Window::Window(const std::string &title, int windowWidth=640, int height=320) {
//    if(SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
//        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
//        exit(1);
//    }
//    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, height, SDL_WINDOW_SHOWN);
//    if(window == nullptr) {
//        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//        exit(1);
//    }
//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    if(renderer == nullptr) {
//        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//        exit(1);
//    }
//    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//    clear();
//}
//
//void Window::clear() {
//    SDL_RenderClear(renderer);
//
//}
//
//
//Window::~Window() {
//    SDL_DestroyWindow(window);
//    SDL_DestroyRenderer(renderer);
//    SDL_Quit();
//}
//
//
//void Window::draw(bool pixels[64*32]) {
//    // draw the pixels to the screen
//    for(int y=0;y<32;++y) {
//        for(int x=0;x<64;++x) {
//            if(pixels[y*64+x]) {
//                SDL_Rect pixel = {x*10, y*10, 10, 10};
//                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
//                SDL_RenderFillRect(renderer, &pixel);
//            }
//        }
//    }
//    SDL_RenderPresent(renderer);
//}
//
//void Window::handle_events() {
//SDL_Event event;
//    while(SDL_PollEvent(&event)) {
//        if(event.type == SDL_QUIT) {
//            closed = true;
//        }
//    }
//}
//
//
//void Window::close() {
//    // close the window, exit and clean up
//    closed = true;
//    SDL_DestroyWindow(window);
//    SDL_DestroyRenderer(renderer);
//
//    SDL_Quit();
//}
//
//bool Window::is_closed() {
//    return closed;
//}
//
//void Window::update() {
//
//}
Window::Window(const char *title, int windowWidth, int windowHeight, int textureWidth, int textureHeight) {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(title, 0, 0,
                              windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(
            renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
            textureWidth, textureHeight);
}

void Window::draw(const void *buffer) {
    if (SDL_UpdateTexture(texture, nullptr, buffer, 256) < 0 ){
        std::cout << "SDL_UpdateTexture error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    if(SDL_RenderClear(renderer) < 0 ) {
        std::cout << "SDL_RenderClear error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    if (SDL_RenderCopy(renderer, texture, nullptr, nullptr) < 0 ){
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