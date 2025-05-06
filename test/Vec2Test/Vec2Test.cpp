#include "gtest/gtest.h"

#include "math/Vec2.hpp"

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
