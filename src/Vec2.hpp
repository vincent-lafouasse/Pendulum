#pragma once

#include <cmath>

#include <raylib.h>
#include <raymath.h>

class Vec2 {
    Vec2(float x, float y): self{x, y} {}

    Vec2(Vector2 v): self(v) {}
    [[nodiscard]]Vector2 get() const { return self; }

    [[nodiscard]]static Vec2 sub(Vec2 a, Vec2 b) {
        return Vector2Subtract(a.get(), b.get());
    }
    [[nodiscard]]Vec2 sub(Vec2 other) const {
        return Vec2::sub(*this, other);
    }

    [[nodiscard]]static Vec2 add(Vec2 a, Vec2 b) {
        return Vector2Add(a.get(), b.get());
    }
    [[nodiscard]]Vec2 add(Vec2 other) const {
        return Vec2::add(*this, other);
    }

    [[nodiscard]]static Vec2 negate(Vec2 v) {
        return Vector2Negate(v.get());
    }
    [[nodiscard]]Vec2 negated() const {
        return Vec2::negate(*this);
    }
    void negate() {
        *this = this->negated();
    }


    [[nodiscard]]static Vec2 scale(Vec2 v, float f) {
        return Vector2Scale(v.get(), f);
    }
    [[nodiscard]]Vec2 scaled(float f) const {
        return Vec2::scale(*this, f);
    }
    void scale(float f) {
        *this = this->scaled(f);
    }

    [[nodiscard]]static Vec2 subValue(Vec2 v, float f) {
        return Vector2SubtractValue(v.get(), f);
    }
    [[nodiscard]]Vec2 subValue(float f) const {
        return Vec2::subValue(*this, f);
    }

    [[nodiscard]]static Vec2 addValue(Vec2 v, float f) {
        return Vector2AddValue(v.get(), f);
    }
    [[nodiscard]]Vec2 addValue(float f) const {
        return Vec2::addValue(*this, f);
    }

    bool operator==(Vec2 other) const {
        return Vector2Equals(this->get(), other.get());
    }

    [[nodiscard]]float& x() { return self.x; }
    [[nodiscard]]float x() const { return self.x; }
    [[nodiscard]]float& y() { return self.y; }
    [[nodiscard]]float y() const { return self.y; }
private:
    Vector2 self;
};
