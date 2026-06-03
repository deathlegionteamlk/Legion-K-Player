#include "UI.hpp"

UI::UI(SDL_Renderer* renderer) : renderer(renderer) {
    initLayout();
}

void UI::initLayout() {
    sidebarButtons.push_back({{1210, 20, 60, 60}, {100, 100, 255, 255}, "Home"});
    sidebarButtons.push_back({{1210, 100, 60, 60}, {100, 100, 255, 255}, "Back"});
    sidebarButtons.push_back({{1210, 180, 60, 60}, {100, 100, 255, 255}, "Recents"});
    sidebarButtons.push_back({{1210, 260, 60, 60}, {100, 100, 255, 255}, "Volume"});
    sidebarButtons.push_back({{1210, 640, 60, 60}, {150, 150, 150, 255}, "Set"});

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 6; ++j) {
            appIcons.push_back({{80 + j * 180, 80 + i * 140, 100, 100}, {70, 130, 230, 255}, "App"});
        }
    }
}

void UI::handleEvent(SDL_Event& e, KEngine& engine) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x;
        int y = e.button.y;
        for (auto& btn : sidebarButtons) {
            if (x >= btn.rect.x && x <= btn.rect.x + btn.rect.w && y >= btn.rect.y && y <= btn.rect.y + btn.rect.h) {
                if (btn.label == "Home") engine.reset();
            }
        }
    }
}

void UI::render(KEngine& engine) {
    (void)engine;
    SDL_SetRenderDrawColor(renderer, 15, 25, 50, 255);
    SDL_Rect sidebar = {1200, 0, 80, 720};
    SDL_RenderFillRect(renderer, &sidebar);

    SDL_SetRenderDrawColor(renderer, 30, 40, 80, 255);
    SDL_RenderDrawLine(renderer, 1200, 0, 1200, 720);

    for (auto& btn : sidebarButtons) {
        SDL_SetRenderDrawColor(renderer, btn.color.r, btn.color.g, btn.color.b, btn.color.a);
        SDL_RenderFillRect(renderer, &btn.rect);
        SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);
        SDL_RenderDrawRect(renderer, &btn.rect);
    }

    for (auto& icon : appIcons) {
        SDL_SetRenderDrawColor(renderer, icon.color.r, icon.color.g, icon.color.b, icon.color.a);
        SDL_RenderFillRect(renderer, &icon.rect);
        SDL_SetRenderDrawColor(renderer, 100, 180, 255, 255);
        SDL_RenderDrawRect(renderer, &icon.rect);
    }
}
