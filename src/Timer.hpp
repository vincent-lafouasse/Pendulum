#pragma once

#include <SDL_timer.h>

#include <stdexcept>

#include "Config.hpp"

class Timer final {
   public:
    using UInt = decltype(SDL_GetTicks());

    Timer() : ms_per_frame(Config::ms_per_frame), frame_start_is_init(false) {}

    void start_frame() {
        this->frame_start_ms = SDL_GetTicks();
        this->frame_start_is_init = true;
    }

    void cap_frame() {
        if (!this->frame_start_is_init) {
            throw UninitializedFrame();
        }

        const UInt frame_end_ms = SDL_GetTicks();
        const UInt time_to_wait =
            this->ms_per_frame - (frame_end_ms - this->frame_start_ms);

        if (time_to_wait > 0) {
            SDL_Delay(time_to_wait);
        }
        this->frame_start_is_init = false;
    }

    class UninitializedFrame : public std::runtime_error {
       public:
        UninitializedFrame()
            : std::runtime_error("Attempting to cap uninitialized frame") {}
    };

   private:
    const UInt ms_per_frame;
    UInt frame_start_ms;
    bool frame_start_is_init;
};
