#include "Vec2.hpp"

#include <sstream>

#include "./math.hpp"

Vec2::Scalar Vec2::magnitude() const {
    return std::sqrt(this->dot(*this));
}

void Vec2::normalize() {
    *this /= this->magnitude();
}

Vec2::Scalar Vec2::dot(Vec2 other) const {
    return Vec2::dot(*this, other);
}

Vec2::Scalar Vec2::dot(Vec2 lhs, Vec2 rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Vec2::Scalar Vec2::determinant(Vec2 other) const {
    return Vec2::determinant(*this, other);
}

Vec2::Scalar Vec2::determinant(Vec2 lhs, Vec2 rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

bool Vec2::is_aligned_with(Vec2 other) const {
    return float_equal(this->determinant(other), 0.0f);
}

bool Vec2::is_orthogonal_to(Vec2 other) const {
    return float_equal(this->dot(other), 0.0f);
}

std::string Vec2::repr() const {
    std::stringstream s;

    s << "Vec2 { " << x << ", " << y << " }";
    return s.str();
}
