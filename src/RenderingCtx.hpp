#pragma once

#include <SDL2/SDL.h>

struct RenderingCtx final {
    RenderingCtx();
    ~RenderingCtx();
    void render(/* pass world later */);

    SDL_Window* window;
    SDL_Renderer* renderer;
};
