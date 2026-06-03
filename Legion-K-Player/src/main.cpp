#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include "KEngine.hpp"
#include "UI.hpp"

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--test") {
        KEngine engine;
        std::vector<Instruction> prog = {
            {OpCode::LDI, 0, 0, 10},
            {OpCode::LDI, 1, 0, 20},
            {OpCode::ADD, 0, 1, 0},
            {OpCode::PRT, 0, 0, 0},
            {OpCode::HALT, 0, 0, 0}
        };
        engine.loadProgram(prog);
        engine.run();
        return 0;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return 1;
    if (TTF_Init() == -1) return 1;

    SDL_Window* window = SDL_CreateWindow("Legion K Player - Full Version", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    if (!window) return 1;

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return 1;

    UI ui(renderer);
    KEngine engine;

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
            ui.handleEvent(e, engine);
        }

        SDL_SetRenderDrawColor(renderer, 10, 20, 40, 255);
        SDL_RenderClear(renderer);

        ui.render(engine);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
