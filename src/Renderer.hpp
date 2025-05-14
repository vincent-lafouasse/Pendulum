#pragma once

#include <SDL2/SDL.h>

#include "World.hpp"

struct Renderer final {
    Renderer();
    ~Renderer();

    void render(const World& world) const;
    void set_render_color(SDL_Color color) const;

    SDL_Window* window;
    SDL_Renderer* renderer;
};
