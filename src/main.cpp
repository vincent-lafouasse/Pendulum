#include <SDL2/SDL.h>

#include "RenderingCtx.hpp"
#include "Timer.hpp"

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
