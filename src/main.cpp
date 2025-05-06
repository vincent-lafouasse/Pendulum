#include <SDL2/SDL.h>

#include "Renderer.hpp"
#include "Timer.hpp"
#include "World.hpp"

int main() {
    Config::log();

    Renderer renderer{};
    Timer timer{};

    World world{};

    SDL_Event event;
    while (true) {
        timer.start_frame();
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }

        renderer.render(world);

        timer.cap_frame();
    }

    return (EXIT_SUCCESS);
}
