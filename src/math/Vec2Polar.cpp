#include "Vec2.hpp"
#include "math/math.hpp"

Vec2 Vec2::as_polar() const {
    Scalar radius = this->magnitude();

    if (float_equal(radius, 0.0f)) {
        return {0.0f, 0.0f};
    }

    Scalar det = Vec2::determinant(Vec2::ex(), *this);
    Scalar inner = Vec2::dot(Vec2::ex(), *this);
    Scalar angle = std::atan2(det, inner);
    if (angle < 0.0) {
        angle += Constants::Tau;
    }

    return {radius, angle};
}

Vec2 Vec2::as_cartesian() const {
    Vec2 unit{std::cos(this->theta()), std::sin(this->theta())};

    return this->r() * unit;
}

Vec2::Scalar Vec2::r() const {
    return this->x;
}

Vec2::Scalar Vec2::theta() const {
    return this->y;
}

Vec2::Scalar& Vec2::r() {
    return this->x;
}

Vec2::Scalar& Vec2::theta() {
    return this->y;
}
