#pragma once

#include "Config.hpp"
#include "shapes/Sphere.hpp"

struct World final {
    World() : ball{{2.0f, 2.0f}, 1.0f} {}

    Sphere ball;
};
