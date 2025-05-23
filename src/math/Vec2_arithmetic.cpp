#include "Vec2.hpp"

#include "./math.hpp"

Vec2 operator+(Vec2 lhs, Vec2 rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

Vec2 operator-(Vec2 v) {
    return {-v.x, -v.y};
}

Vec2 operator-(Vec2 lhs, Vec2 rhs) {
    return lhs + (-rhs);
}

Vec2 operator*(Vec2::Scalar s, Vec2 rhs) {
    return {s * rhs.x, s * rhs.y};
}

Vec2 operator/(Vec2 lhs, Vec2::Scalar s) {
    return (1.0f / s) * lhs;
}

Vec2 Vec2::operator+=(Vec2 other) {
    *this = *this + other;
    return *this;
}

Vec2 Vec2::operator-=(Vec2 other) {
    *this = *this - other;
    return *this;
}

Vec2 Vec2::operator*=(Scalar s) {
    *this = s * *this;
    return *this;
}

Vec2 Vec2::operator/=(Scalar s) {
    *this = *this / s;
    return *this;
}

bool Vec2::operator==(Vec2 other) const {
    return float_equal(this->x, other.x) && float_equal(this->y, other.y);
}

bool Vec2::operator!=(Vec2 other) const {
    return !(*this == other);
}
