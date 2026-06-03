#ifndef K_INTERFACE_HPP
#define K_INTERFACE_HPP
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "core/KVirtualMachine.hpp"
struct K_WIDGET {
    SDL_Rect area;
    SDL_Color tone;
    std::string tag;
};
class KInterface {
public:
    KInterface(SDL_Renderer* context);
    void process(SDL_Event& event, KVirtualMachine& vm);
    void draw(KVirtualMachine& vm);
private:
    SDL_Renderer* ctx;
    std::vector<K_WIDGET> deck;
    std::vector<K_WIDGET> grid;
    void build();
};
#endif
