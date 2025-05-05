#include <SDL2/SDL.h>

struct Config final {
    static constexpr float aspect_ratio = 16.0f / 9.0f;
    static constexpr size_t width = 800;
    static constexpr size_t height = static_cast<size_t>(width / aspect_ratio);
    static constexpr float target_fps = 10.0f;
    static constexpr size_t ms_per_frame =
        static_cast<size_t>(1000.0f / target_fps);
};

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

   public:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#define NICE_BLUE 33, 118, 174, 255

void cap_fps(uint32_t frame_beginning_tick);

int main() {
    RenderingCtx ctx{};

    SDL_Event event;

    while (true) {
        const uint32_t frame_beginning_tick = SDL_GetTicks();
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }

        SDL_SetRenderDrawColor(ctx.renderer, NICE_BLUE);
        SDL_RenderClear(ctx.renderer);

        SDL_RenderPresent(ctx.renderer);

        cap_fps(frame_beginning_tick);
    }
    return (EXIT_SUCCESS);
}
void cap_fps(uint32_t frame_beginning_tick) {
    const uint32_t frame_end_tick = SDL_GetTicks();
    const uint32_t time_to_wait =
        Config::ms_per_frame - (frame_end_tick - frame_beginning_tick);

    if (time_to_wait > 0) {
        SDL_Delay(time_to_wait);
    }
}
