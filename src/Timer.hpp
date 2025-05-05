#pragma once

#include <SDL_timer.h>

#include <stdexcept>

class Timer final {
   public:
    Timer();

    void start_frame();
    void cap_frame();

    class UninitializedFrame : public std::runtime_error {
       public:
        UninitializedFrame();
    };

   private:
    using UInt = decltype(SDL_GetTicks());

    const UInt ms_per_frame;
    UInt frame_start_ms;
    bool frame_start_is_init;
};
