#include <SDL2/SDL.h>

struct Config final {
    static constexpr float aspect_ratio = 16.0f / 9.0f;
    static constexpr size_t width = 800;
    static constexpr size_t height = static_cast<size_t>(width / aspect_ratio);
    static constexpr float target_fps = 10.0f;
    static constexpr size_t ms_per_frame =
        static_cast<size_t>(1000.0f / target_fps);
};

#define NICE_BLUE 33, 118, 174, 255

void cap_fps(uint32_t frame_beginning_tick);
void init_SDL(SDL_Window** return_window, SDL_Renderer** return_renderer);

int main() {
    SDL_Window* window;
    SDL_Renderer* renderer;
    init_SDL(&window, &renderer);

    SDL_Event event;

    while (true) {
        const uint32_t frame_beginning_tick = SDL_GetTicks();
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, NICE_BLUE);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);

        cap_fps(frame_beginning_tick);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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

void init_SDL(SDL_Window** return_window, SDL_Renderer** return_renderer) {
    constexpr int SCREEN_X_POS = 0;
    constexpr int SCREEN_Y_POS = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    *return_window =
        SDL_CreateWindow("a window", SCREEN_X_POS, SCREEN_Y_POS, Config::width,
                         Config::height, SDL_WINDOW_OPENGL);
    if (*return_window == nullptr) {
        SDL_Log("Could not create a window: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    *return_renderer =
        SDL_CreateRenderer(*return_window, -1, SDL_RENDERER_ACCELERATED);
    if (*return_renderer == nullptr) {
        SDL_Log("Could not create a renderer: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}
