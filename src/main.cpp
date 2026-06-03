#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "core/KVirtualMachine.hpp"
#include "ui/KInterface.hpp"
#include <vector>
int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--test") {
        KVirtualMachine vm;
        std::vector<K_INS> boot_image = {
            {K_OP::REG_LOAD, 0, 0, 100},
            {K_OP::REG_LOAD, 1, 0, 200},
            {K_OP::ALU_ADD,  0, 1, 0},
            {K_OP::OUT_PRT,  0, 0, 0},
            {K_OP::SYS_HALT, 0, 0, 0}
        };
        vm.boot(boot_image);
        vm.cycle();
        return 0;
    }
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
    SDL_Window* win = SDL_CreateWindow("Legion K Player | Client", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    if (!win) return 1;
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren) return 1;
    KVirtualMachine vm;
    KInterface ui(ren);
    bool run = true;
    SDL_Event ev;
    while (run) {
        while (SDL_PollEvent(&ev) != 0) {
            if (ev.type == SDL_QUIT) run = false;
            ui.process(ev, vm);
        }
        SDL_SetRenderDrawColor(ren, 5, 10, 25, 255);
        SDL_RenderClear(ren);
        ui.draw(vm);
        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
