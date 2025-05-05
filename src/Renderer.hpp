#pragma once

#include <SDL2/SDL.h>

#include "World.hpp"

struct Renderer final {
    Renderer();
    ~Renderer();
    void render(const World& world) const;

    SDL_Window* window;
    SDL_Renderer* renderer;
};
