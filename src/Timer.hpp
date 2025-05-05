#pragma once

#include <SDL_timer.h>

#include "Config.hpp"

class Timer final {
   public:
    using UInt = decltype(SDL_GetTicks());

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
