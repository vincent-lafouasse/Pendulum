#pragma once

#include "math/Vec2.hpp"

struct Sphere final {
    bool contains(Point2 point) const {
        return (point - center).magnitude() <= radius * radius;
    }

    Point2 center;
    float radius;
};
