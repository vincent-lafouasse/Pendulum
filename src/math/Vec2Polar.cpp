#include "Vec2.hpp"
#include "math/math.hpp"

Vec2 Vec2::as_polar() const {
    Scalar radius = this->magnitude();

    if (float_equal(radius, 0.0f)) {
        return {0.0f, 0.0f};
    }

    return {radius,
            std::atan2(this->determinant(Vec2::ref()), this->dot(Vec2::ref()))};
}

Vec2 Vec2::as_cartesian() const {
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
