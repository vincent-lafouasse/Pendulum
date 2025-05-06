#include "Renderer.hpp"

#include "Config.hpp"
#include "Viewport.hpp"

Renderer::Renderer() {
    constexpr int screen_x_pos = 0;
    constexpr int screen_y_pos = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    this->window =
        SDL_CreateWindow("a window", screen_x_pos, screen_y_pos, Config::width,
                         Config::height, SDL_WINDOW_OPENGL);
    if (this->window == nullptr) {
        SDL_Log("Could not create a window: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    this->renderer =
        SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (this->renderer == nullptr) {
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

namespace {
Point2 compute_pixel(int x, int y) {
    return Viewport::pixel00 +
           Viewport::delta * Vec2{static_cast<float>(x), static_cast<float>(y)};
}
}  // namespace

void Renderer::render(const World& world) const {
    (void)world;
    SDL_SetRenderDrawColor(this->renderer, 33, 118, 174, 255);  // blue
    SDL_RenderClear(this->renderer);

    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);  // black
    for (int y = 0; y < Config::height; ++y) {
        for (int x = 0; x < Config::width; ++x) {
            const Point2 pixel = compute_pixel(x, y);

            if (world.ball.contains(pixel)) {
                SDL_RenderDrawPoint(this->renderer, x, y);
            }
        }
    }

    SDL_RenderPresent(this->renderer);
}
