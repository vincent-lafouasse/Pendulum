#include "Timer.hpp"

Timer::Timer()
    : ms_per_frame(Config::ms_per_frame), frame_start_is_init(false) {}

void Timer::start_frame() {
    this->frame_start_ms = SDL_GetTicks();
    this->frame_start_is_init = true;
}

void Timer::cap_frame() {
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

Timer::UninitializedFrame::UninitializedFrame()
    : std::runtime_error("Attempting to cap uninitialized frame") {}
