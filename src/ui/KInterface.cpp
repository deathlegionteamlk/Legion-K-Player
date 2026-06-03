#include "ui/KInterface.hpp"
KInterface::KInterface(SDL_Renderer* context) : ctx(context) {
    build();
}
void KInterface::build() {
    deck.push_back({{1210, 20, 60, 60}, {80, 120, 255, 255}, "HOME"});
    deck.push_back({{1210, 100, 60, 60}, {80, 120, 255, 255}, "BACK"});
    deck.push_back({{1210, 180, 60, 60}, {80, 120, 255, 255}, "APPS"});
    deck.push_back({{1210, 260, 60, 60}, {80, 120, 255, 255}, "VOL+"});
    deck.push_back({{1210, 340, 60, 60}, {80, 120, 255, 255}, "VOL-"});
    deck.push_back({{1210, 640, 60, 60}, {180, 180, 200, 255}, "SET"});
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 6; ++c) {
            grid.push_back({{100 + c * 180, 100 + r * 140, 120, 120}, {60, 140, 240, 255}, "CELL"});
        }
    }
}
void KInterface::process(SDL_Event& event, KVirtualMachine& vm) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x = event.button.x;
        int y = event.button.y;
        for (auto& w : deck) {
            if (x >= w.area.x && x <= w.area.x + w.area.w && y >= w.area.y && y <= w.area.y + w.area.h) {
                if (w.tag == "HOME") vm.flush();
            }
        }
    }
}
void KInterface::draw(KVirtualMachine& vm) {
    (void)vm;
    SDL_SetRenderDrawColor(ctx, 10, 20, 45, 255);
    SDL_Rect bar = {1200, 0, 80, 720};
    SDL_RenderFillRect(ctx, &bar);
    SDL_SetRenderDrawColor(ctx, 40, 60, 100, 255);
    SDL_RenderDrawLine(ctx, 1200, 0, 1200, 720);
    for (auto& w : deck) {
        SDL_SetRenderDrawColor(ctx, w.tone.r, w.tone.g, w.tone.b, w.tone.a);
        SDL_RenderFillRect(ctx, &w.area);
        SDL_SetRenderDrawColor(ctx, 220, 230, 255, 255);
        SDL_RenderDrawRect(ctx, &w.area);
    }
    for (auto& w : grid) {
        SDL_SetRenderDrawColor(ctx, w.tone.r, w.tone.g, w.tone.b, w.tone.a);
        SDL_RenderFillRect(ctx, &w.area);
        SDL_SetRenderDrawColor(ctx, 120, 200, 255, 255);
        SDL_RenderDrawRect(ctx, &w.area);
    }
}
