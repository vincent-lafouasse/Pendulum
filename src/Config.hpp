#pragma once

#include <cstddef>
#include <iostream>

namespace Config {
constexpr float aspect_ratio = 3.0f / 2.0f;
constexpr int width = 300;
constexpr int height = static_cast<int>(width / aspect_ratio);

constexpr float target_fps = 10.0f;
constexpr size_t ms_per_frame = static_cast<size_t>(1000.0f / target_fps);

static inline void log() {
    std::clog << "Config {\n";
    std::clog << "\taspect_ratio: " << aspect_ratio << ",\n";
    std::clog << "\twidth: " << width << ",\n";
    std::clog << "\theight: " << height << ",\n";
    std::clog << "\ttarget_fps: " << target_fps << ",\n";
    std::clog << "\tms_per_frame: " << ms_per_frame << ",\n";
    std::clog << "}\n";
}
};  // namespace Config
