#pragma once

#include "Config.hpp"
#include "shapes/Sphere.hpp"

struct World final {
    World()
        : height{10.0f},
          width{10.0f / Config::aspect_ratio},
          ball{{2.0f, 2.0f}, 1.0f} {}

    const float height;
    const float width;

    Sphere ball;
};
