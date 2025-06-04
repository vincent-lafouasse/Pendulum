#pragma once

#include <cmath>

#include <raylib.h>
#include <raymath.h>

class Vec2 {
    Vec2(float x, float y): self{x, y} {}
    Vec2(Vector2 v): self(v) {}

    float& x() { return self.x; }
    float x() const { return self.x; }
    float& y() { return self.y; }
    float y() const { return self.y; }
    Vector2 get() const { return self; }
private:
    Vector2 self;
};
