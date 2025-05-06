#pragma once

#include <string>

struct Vec2 final {
    using Scalar = float;

    [[nodiscard]] Scalar magnitude() const;
    void normalize();

    [[nodiscard]] Scalar dot(Vec2 other) const;
    [[nodiscard]] static Scalar dot(Vec2 lhs, Vec2 rhs);

    [[nodiscard]] Vec2 cross(Vec2 other) const;
    [[nodiscard]] static Vec2 cross(Vec2 lhs, Vec2 rhs);

    [[nodiscard]] bool is_aligned_with(Vec2 other) const;
    [[nodiscard]] bool is_orthogonal_to(Vec2 other) const;

    Vec2 operator+=(Vec2 other);
    Vec2 operator-=(Vec2 other);
    Vec2 operator*=(Scalar s);
    Vec2 operator/=(Scalar s);

    bool operator==(Vec2 other) const;
    bool operator!=(Vec2 other) const;

    [[nodiscard]] std::string repr() const;

    Scalar x;
    Scalar y;
};

Vec2 operator+(Vec2 lhs, Vec2 rhs);
Vec2 operator-(Vec2 lhs, Vec2 rhs);
Vec2 operator-(Vec2 v);

Vec2 operator*(Vec2::Scalar s, Vec2 rhs);
Vec2 operator/(Vec2 lhs, Vec2::Scalar s);

using Point2 = Vec2;
