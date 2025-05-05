#pragma once

#include <SDL_timer.h>

#include <stdexcept>

#include "Config.hpp"

class Timer final {
   public:
    using UInt = decltype(SDL_GetTicks());

    Timer();

    void start_frame();
    void cap_frame();

    class UninitializedFrame : public std::runtime_error {
       public:
        UninitializedFrame();
    };

   private:
    const UInt ms_per_frame;
    UInt frame_start_ms;
    bool frame_start_is_init;
};
