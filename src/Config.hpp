#pragma once

#include <cstddef>

struct Config final {
    static constexpr float aspect_ratio = 16.0f / 9.0f;
    static constexpr size_t width = 800;
    static constexpr size_t height = static_cast<size_t>(width / aspect_ratio);
    static constexpr float target_fps = 10.0f;
    static constexpr size_t ms_per_frame =
        static_cast<size_t>(1000.0f / target_fps);
};
