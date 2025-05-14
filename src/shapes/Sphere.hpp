#pragma once

#include "math/Vec2.hpp"

struct Sphere final {
    bool contains(Point2 point) const {
        return (point - center).magnitude() <= radius * radius;
    }

    void translate_to(Point2 p) { this->center = p; }
    void translate_by(Vec2 v) { this->center += v; }

    Point2 center;
    float radius;
};
