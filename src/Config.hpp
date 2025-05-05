#pragma once

#include <cstddef>

namespace Config {
constexpr float aspect_ratio = 16.0f / 9.0f;
constexpr size_t width = 800;
constexpr size_t height = static_cast<size_t>(width / aspect_ratio);

constexpr float viewport_height = 10.0f;
constexpr float viewport_width = viewport_height * aspect_ratio;

constexpr float delta_x = viewport_width / width;
constexpr float delta_y = viewport_height / height;

constexpr float target_fps = 10.0f;
constexpr size_t ms_per_frame = static_cast<size_t>(1000.0f / target_fps);
};  // namespace Config
