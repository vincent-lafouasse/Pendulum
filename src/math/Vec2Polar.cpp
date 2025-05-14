#include "Vec2.hpp"
#include "math/math.hpp"

Vec2 Vec2::as_polar() const {
    Scalar radius = this->magnitude();

    if (float_equal(radius, 0.0f)) {
        return {0.0f, 0.0f};
    }

    Scalar angle =
        std::atan2(this->determinant(Vec2::ref()), this->dot(Vec2::ref()));
    /*
    while (angle < 0.0) {
        angle += Constants::Tau;
    }
    while (angle >= Constants::Tau) {
        angle -= Constants::Tau;
    }
    */

    return {radius, angle};
}

Vec2 Vec2::as_cartesian() const {
    Vec2 unit{std::sin(this->theta()), std::cos(this->theta())};

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
