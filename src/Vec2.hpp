#pragma once

#include <cmath>

#include <raylib.h>
#include <raymath.h>

class Vec2 {
public:
    constexpr Vec2(float x, float y): self{x, y} {}

    constexpr Vec2(Vector2 v): self(v) {}
    [[nodiscard]] constexpr Vector2 get() const { return self; }

    [[nodiscard]]static constexpr Vec2 sub(Vec2 a, Vec2 b) {
        return Vector2Subtract(a.get(), b.get());
    }
    [[nodiscard]]constexpr Vec2 operator-(Vec2 other) const {
        return Vec2::sub(*this, other);
    }

    [[nodiscard]]static constexpr Vec2 add(Vec2 a, Vec2 b) {
        return Vector2Add(a.get(), b.get());
    }
    [[nodiscard]]constexpr Vec2 operator+(Vec2 other) const {
        return Vec2::add(*this, other);
    }

    [[nodiscard]]static constexpr Vec2 negate(Vec2 v) {
        return Vector2Negate(v.get());
    }
    [[nodiscard]]constexpr Vec2 operator-() const {
        return Vec2::negate(*this);
    }
    constexpr void negate() {
        *this = -*this;
    }


    [[nodiscard]]static constexpr Vec2 scale(Vec2 v, float f) {
        return Vector2Scale(v.get(), f);
    }
    [[nodiscard]]constexpr Vec2 scaled(float f) const {
        return Vec2::scale(*this, f);
    }
    constexpr void scale(float f) {
        *this = this->scaled(f);
    }

    [[nodiscard]]static constexpr Vec2 subValue(Vec2 v, float f) {
        return Vector2SubtractValue(v.get(), f);
    }
    [[nodiscard]]constexpr Vec2 subValue(float f) const {
        return Vec2::subValue(*this, f);
    }

    [[nodiscard]]static constexpr Vec2 addValue(Vec2 v, float f) {
        return Vector2AddValue(v.get(), f);
    }
    [[nodiscard]]constexpr Vec2 addValue(float f) const {
        return Vec2::addValue(*this, f);
    }

    [[nodiscard]]static constexpr float dot(Vec2 a, Vec2 b) {
        return a.x() * b.x() + a.y() * b.y();
    }
    [[nodiscard]]constexpr float dot(Vec2 other) const {
        return Vec2::dot(*this, other);
    }

    [[nodiscard]]constexpr float magnitude() const {
        return std::sqrt(this->dot(*this));
    }

    [[nodiscard]]constexpr Vec2 normalized() const {
        return this->scaled(1.0f / this->magnitude());
    }

    [[nodiscard]]constexpr Vec2 transverse() const {
        return {-y(), x()};
    }


    constexpr bool operator==(Vec2 other) const {
        return Vector2Equals(this->get(), other.get());
    }

    [[nodiscard]]constexpr float& x() { return self.x; }
    [[nodiscard]]constexpr float x() const { return self.x; }
    [[nodiscard]]constexpr float& y() { return self.y; }
    [[nodiscard]]constexpr float y() const { return self.y; }
private:
    Vector2 self;
};
