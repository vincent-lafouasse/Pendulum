#include <SDL2/SDL.h>

#include "Config.hpp"
#include "Timer.hpp"

class RenderingCtx final {
   public:
    RenderingCtx() {
        constexpr int screen_x_pos = 0;
        constexpr int screen_y_pos = 0;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        this->window =
            SDL_CreateWindow("a window", screen_x_pos, screen_y_pos,
                             Config::width, Config::height, SDL_WINDOW_OPENGL);
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

    ~RenderingCtx() {
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        SDL_Quit();
    }

    void render(/* pass world later */) {
        SDL_SetRenderDrawColor(this->renderer, 33, 118, 174, 255);  // blue
        SDL_RenderClear(this->renderer);

        SDL_RenderPresent(this->renderer);
    }

   private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

int main() {
    RenderingCtx ctx{};
    Timer timer{};

    SDL_Event event;
    while (true) {
        timer.start_frame();
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }

        ctx.render();

        timer.cap_frame();
    }

    return (EXIT_SUCCESS);
}
