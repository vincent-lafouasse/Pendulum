#include "Vec2.hpp"
#include "math/math.hpp"

Vec2 Vec2::as_polar(Vec2 origin) const {
    Vec2 to_point = *this - origin;
    Scalar radius = to_point.magnitude();

    if (float_equal(radius, 0.0f)) {
        return {0.0f, 0.0f};
    }


    to_point.normalize();
    return {};
}

Vec2 Vec2::as_cartesian(Vec2 origin) {
    return {};
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
