#ifndef UI_HPP
#define UI_HPP

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "KEngine.hpp"

struct ButtonUI {
    SDL_Rect rect;
    SDL_Color color;
    std::string label;
};

class UI {
public:
    UI(SDL_Renderer* renderer);
    void handleEvent(SDL_Event& e, KEngine& engine);
    void render(KEngine& engine);

private:
    SDL_Renderer* renderer;
    std::vector<ButtonUI> sidebarButtons;
    std::vector<ButtonUI> appIcons;
    void initLayout();
};

#endif
