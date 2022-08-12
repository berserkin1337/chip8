//
// Created by aviral on 7/19/22.
//

#include "Chip8.h"
#include "Window.h"
void Chip8::emulate() {
    // Fetch the next instruction
    const double frameDelay = (1000.0 / 60.0);
    SDL_Event event;
    uint32_t frameStart = SDL_GetTicks();


    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                closed = true;
            } break;

            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    {
                        closed = true;
                    } break;

                    case SDLK_x:
                    {
                        keypad[0] = 1;
                    } break;

                    case SDLK_1:
                    {
                        keypad[1] = 1;
                    } break;

                    case SDLK_2:
                    {
                        keypad[2] = 1;
                    } break;

                    case SDLK_3:
                    {
                        keypad[3] = 1;
                    } break;

                    case SDLK_q:
                    {
                        keypad[4] = 1;
                    } break;

                    case SDLK_w:
                    {
                        keypad[5] = 1;
                    } break;

                    case SDLK_e:
                    {
                        keypad[6] = 1;
                    } break;

                    case SDLK_a:
                    {
                        keypad[7] = 1;
                    } break;

                    case SDLK_s:
                    {
                        keypad[8] = 1;
                    } break;

                    case SDLK_d:
                    {
                        keypad[9] = 1;
                    } break;

                    case SDLK_z:
                    {
                        keypad[0xA] = 1;
                    } break;

                    case SDLK_c:
                    {
                        keypad[0xB] = 1;
                    } break;

                    case SDLK_4:
                    {
                        keypad[0xC] = 1;
                    } break;

                    case SDLK_r:
                    {
                        keypad[0xD] = 1;
                    } break;

                    case SDLK_f:
                    {
                        keypad[0xE] = 1;
                    } break;

                    case SDLK_v:
                    {
                        keypad[0xF] = 1;
                    } break;
                }
            } break;

            case SDL_KEYUP:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_x:
                    {
                        keypad[0] = 0;
                    } break;

                    case SDLK_1:
                    {
                        keypad[1] = 0;
                    } break;

                    case SDLK_2:
                    {
                        keypad[2] = 0;
                    } break;

                    case SDLK_3:
                    {
                        keypad[3] = 0;
                    } break;

                    case SDLK_q:
                    {
                        keypad[4] = 0;
                    } break;

                    case SDLK_w:
                    {
                        keypad[5] = 0;
                    } break;

                    case SDLK_e:
                    {
                        keypad[6] = 0;
                    } break;

                    case SDLK_a:
                    {
                        keypad[7] = 0;
                    } break;

                    case SDLK_s:
                    {
                        keypad[8] = 0;
                    } break;

                    case SDLK_d:
                    {
                        keypad[9] = 0;
                    } break;

                    case SDLK_z:
                    {
                        keypad[0xA] = 0;
                    } break;

                    case SDLK_c:
                    {
                        keypad[0xB] = 0;
                    } break;

                    case SDLK_4:
                    {
                        keypad[0xC] = 0;
                    } break;

                    case SDLK_r:
                    {
                        keypad[0xD] = 0;
                    } break;

                    case SDLK_f:
                    {
                        keypad[0xE] = 0;
                    } break;

                    case SDLK_v:
                    {
                        keypad[0xF] = 0;
                    } break;
                }
            } break;
        }
    }

    fetch_instruction();

    // Decode and Execute the instruction
    decode_instruction();

    // Draw the screen
    if(drawFlag) {
        draw_graphics();
        int frameTime = SDL_GetTicks() - frameStart;
        if(frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    // Check for Events
    if (delayTimer > 0) {
        delayTimer--;
    }
    if (soundTimer > 0) {
        soundTimer--;
    }

    drawFlag = false;

//    int frameTime = SDL_GetTicks() - frameStart;
//    std::cout << frameTime - frameDelay << std::endl;
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
