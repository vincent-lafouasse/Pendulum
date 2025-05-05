#include <SDL2/SDL.h>
#include <SDL_timer.h>

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

    void render(/* pass world later */) {
        SDL_SetRenderDrawColor(this->renderer, 33, 118, 174, 255);  // blue
        SDL_RenderClear(this->renderer);

        SDL_RenderPresent(this->renderer);
    }

   private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

class Timer final {
   public:
    using UInt = uint32_t;  // returned by SDL_GetTicks()

    Timer() : ms_per_frame(Config::ms_per_frame) {}

    void start_frame() { this->frame_start_ms = SDL_GetTicks(); }

    void cap_frame() const {
        const UInt frame_end_ms = SDL_GetTicks();
        const UInt time_to_wait =
            this->ms_per_frame - (frame_end_ms - this->frame_start_ms);

        if (time_to_wait > 0) {
            SDL_Delay(time_to_wait);
        }
    }

   private:
    const UInt ms_per_frame;
    UInt frame_start_ms;
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
