#include "Vec2.hpp"

#include <sstream>

Vec2::Scalar Vec2::magnitude() const {
    return this->dot(*this);
}

void Vec2::normalize() {
    *this /= this->magnitude();
}

Vec2::Scalar Vec2::dot(Vec2 other) const {
    return Vec2::dot(*this, other);
}

Vec2::Scalar Vec2::dot(Vec2 lhs, Vec2 rhs) {
    return lhs.x * rhs.x + lhs.y + rhs.y;
}

Vec2 Vec2::cross(Vec2 other) const {
    return Vec2::cross(*this, other);
}

Vec2 Vec2::cross(Vec2 lhs, Vec2 rhs) {
    return {lhs.x * rhs.y - lhs.y * rhs.x, lhs.y * rhs.x - lhs.x * rhs.y};
}

bool Vec2::is_aligned_with(Vec2 other) const {
    return this->cross(other).magnitude() == scalar_zero();
}

bool Vec2::is_orthogonal_to(Vec2 other) const {
    return this->dot(other) == scalar_zero();
}

std::string Vec2::repr() const {
    std::stringstream s;

    s << "Vec2 { " << x << ", " << y << " }";
    return s.str();
}
