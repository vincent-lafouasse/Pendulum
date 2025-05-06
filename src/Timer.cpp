#include "Timer.hpp"

#include "Config.hpp"

#include <iostream>

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

    const UInt frame_len_ms = SDL_GetTicks() - this->frame_start_ms;

    if (frame_len_ms < ms_per_frame) {
        SDL_Delay(ms_per_frame - frame_len_ms);
    }
    this->frame_start_is_init = false;

    const float actual_frame_len =
        static_cast<float>(SDL_GetTicks() - this->frame_start_ms) / 1000.0f;
    std::clog << "fps: " << static_cast<int>(1.0f / actual_frame_len) << '\n';
}

Timer::UninitializedFrame::UninitializedFrame()
    : std::runtime_error("Attempting to cap uninitialized frame") {}
