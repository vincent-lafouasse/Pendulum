#pragma once

#include "Config.hpp"

namespace Viewport {
constexpr float actual_aspect_ratio =
    static_cast<float>(Config::width) / static_cast<float>(Config::height);

constexpr float viewport_height = 10.0f;
constexpr float viewport_width = viewport_height * actual_aspect_ratio;

constexpr float delta_x = viewport_width / Config::width;
constexpr float delta_y = viewport_height / Config::height;
}  // namespace Viewport