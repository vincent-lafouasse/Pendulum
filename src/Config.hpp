#pragma once

#include <cstddef>

namespace Config {
constexpr float aspect_ratio = 16.0f / 9.0f;
constexpr int width = 800;
constexpr int height = static_cast<int>(width / aspect_ratio);

constexpr float target_fps = 10.0f;
constexpr size_t ms_per_frame = static_cast<size_t>(1000.0f / target_fps);
};  // namespace Config
