#pragma once

#include "Config.hpp"
#include "math/Vec2.hpp"

namespace Viewport {
inline constexpr float actual_aspect_ratio =
    static_cast<float>(Config::width) / static_cast<float>(Config::height);

inline constexpr float viewport_height = 10.0f;
inline constexpr float viewport_width = viewport_height * actual_aspect_ratio;

inline constexpr float delta = viewport_width / Config::width;
inline constexpr Vec2 pixel00 = Vec2{0.5f * Viewport::delta, 0.5f * Viewport::delta};

static inline void log() {
    std::clog << "Viewport {\n";
    std::clog << "\tactual_aspect_ratio: " << actual_aspect_ratio << ",\n";
    std::clog << "\tviewport_width: " << viewport_width << ",\n";
    std::clog << "\tviewport_height: " << viewport_height << ",\n";
    std::clog << "\tdelta: " << delta << ",\n";
    std::clog << "}\n";
}
}  // namespace Viewport
