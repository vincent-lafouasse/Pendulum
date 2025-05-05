#pragma once

#include <string>

struct Vec2 final {
    using Scalar = float;

    Vec2 operator+=(Vec2 other);
    Vec2 operator-=(Vec2 other);
    Vec2 operator*=(Scalar s);
    Vec2 operator/=(Scalar s);

    bool operator==(Vec2 other) const; 
    bool operator!=(Vec2 other) const; 

    std::string repr() const;

    Scalar x;
    Scalar y;
};

Vec2 operator+(Vec2 lhs, Vec2 rhs);
Vec2 operator-(Vec2 lhs, Vec2 rhs);

Vec2 operator*(Vec2::Scalar s, Vec2 rhs);
Vec2 operator/(Vec2 lhs, Vec2::Scalar s);
