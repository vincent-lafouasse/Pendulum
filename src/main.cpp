#include <SDL2/SDL.h>

#include "Config.hpp"
#include "RenderingCtx.hpp"
#include "Timer.hpp"

struct Sphere final {
    float center_x;
    float center_y;
    float radius;
};

struct World final {
    World()
        : width{10.0f},
          height{10.0f / Config::aspect_ratio},
          ball{2.0f, 2.0f, 1.0f} {}

    const float width;
    const float height;

    Sphere ball;
};

int main() {
    RenderingCtx ctx{};
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

        ctx.render();

        timer.cap_frame();
    }

    return (EXIT_SUCCESS);
}
