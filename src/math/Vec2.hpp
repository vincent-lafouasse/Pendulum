#pragma once

#include <string>

struct Vec2 final {
    std::string repr() const;

    float x;
    float y;
};
