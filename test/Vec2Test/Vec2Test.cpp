#include "gtest/gtest.h"

#include "math/Vec2.hpp"
#include "math/math.hpp"

#define ASSERT_VEC2_EQUAL(a, b) \
    ASSERT_FLOAT_EQ(a.x, b.x);  \
    ASSERT_FLOAT_EQ(a.y, b.y);

TEST(Vec2, Initialization) {
    Vec2 v{1.0, 2.0};

    ASSERT_FLOAT_EQ(v.x, 1.0);
    ASSERT_FLOAT_EQ(v.y, 2.0);
}

TEST(Vec2, Addition) {
    Vec2 a{1.0, 2.0};
    Vec2 b{3.0, -2.0};

    Vec2 expected{4.0, 0.0};
    Vec2 actual = a + b;

    ASSERT_VEC2_EQUAL(expected, actual);
}

TEST(Vec2, UnaryMinus) {
    Vec2 v{1.0, 2.0};

    Vec2 expected{-1.0, -2.0};
    Vec2 actual = -v;

    ASSERT_VEC2_EQUAL(expected, actual);
}

TEST(Vec2, Subtraction) {
    Vec2 a{1.0, 2.0};
    Vec2 b{3.0, -2.0};

    Vec2 expected{-2.0, 4.0};
    Vec2 actual = a - b;

    ASSERT_VEC2_EQUAL(expected, actual);
}

TEST(Vec2, ExternalMultiplication) {
    Vec2 v{1.0, 2.0};
    Vec2::Scalar s{4.0f};

    Vec2 expected{4.0, 8.0};
    Vec2 actual = s * v;

    ASSERT_VEC2_EQUAL(expected, actual);
}

TEST(Vec2, ExternalDivision) {
    Vec2 v{1.0, 2.0};
    Vec2::Scalar s{4.0f};

    Vec2 expected{0.25, 0.5};
    Vec2 actual = v / s;

    ASSERT_VEC2_EQUAL(expected, actual);
}

TEST(Vec2, UnitVectorsHaveUnitMagnitude) {
    Vec2 ex{1.0, 0.0};
    Vec2 ey{0.0, 1.0};

    float theta1 = 420.69f;
    float theta2 = 1234567890.420f;
    Vec2 u1{std::cos(theta1), std::sin(theta1)};
    Vec2 u2{std::cos(theta2), std::sin(theta2)};

    ASSERT_FLOAT_EQ(ex.magnitude(), 1.0f);
    ASSERT_FLOAT_EQ(ey.magnitude(), 1.0f);
    ASSERT_FLOAT_EQ(u1.magnitude(), 1.0f);
    ASSERT_FLOAT_EQ(u2.magnitude(), 1.0f);
}

TEST(Polar, BasisVectorsHaveCorrectAngle) {
    ASSERT_FLOAT_EQ(Vec2::ex().as_polar().theta(), 0.0f);
    ASSERT_FLOAT_EQ(Vec2::ey().as_polar().theta(), 0.5f * Constants::Pi);
    ASSERT_FLOAT_EQ((-Vec2::ex()).as_polar().theta(), 1.0f * Constants::Pi);
    ASSERT_FLOAT_EQ((-Vec2::ey()).as_polar().theta(), 1.5f * Constants::Pi);
}

TEST(Polar, BackToCartesian) {
    Vec2 ex = Vec2::ex();
    Vec2 ey = Vec2::ey();
    Vec2 cool_vec{420, 69};

    ASSERT_VEC2_EQUAL(ex, ex.as_polar().as_cartesian());
    ASSERT_VEC2_EQUAL(ey, ey.as_polar().as_cartesian());
    ASSERT_VEC2_EQUAL(-ex, (-ex).as_polar().as_cartesian());
    ASSERT_VEC2_EQUAL(-ey, (-ey).as_polar().as_cartesian());
    ASSERT_VEC2_EQUAL(cool_vec, cool_vec.as_polar().as_cartesian());
}
