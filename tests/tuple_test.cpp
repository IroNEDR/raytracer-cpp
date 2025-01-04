#include <cmath>
#include <gtest/gtest.h>
#include "tuple.hpp"


TEST(Tuple, Creation) {
    auto tuple1{ Tuple(2.0f, 1.4f, 3.6f, 1.0f) };
    EXPECT_TRUE(tuple1.isPoint());
    EXPECT_FALSE(tuple1.isVector());
    EXPECT_FLOAT_EQ(tuple1.x(), 2.0f);
    EXPECT_FLOAT_EQ(tuple1.y(), 1.4f);
    EXPECT_FLOAT_EQ(tuple1.z(), 3.6f);
    EXPECT_FLOAT_EQ(tuple1.w(), 1.0f);

    auto tuple2{ Tuple(2.0f, 1.4f, 3.6f, 0.0f) };
    EXPECT_FALSE(tuple2.isPoint());
    EXPECT_TRUE(tuple2.isVector());

    auto tuple3{ Tuple::Point(1.5f, 2.3f, 2.4f)};

    EXPECT_TRUE(tuple3.isPoint());
    EXPECT_FALSE(tuple3.isVector());
    auto tuple4{ Tuple::Vector(1.8f, 2.9f, 3.3f)};
    EXPECT_FALSE(tuple4.isPoint());
    EXPECT_TRUE(tuple4.isVector());
}

TEST(Tuple, Addition) {
    auto point{ Tuple(2.0f, 1.4f, 3.6f, 1.0f) };
    auto vect{ Tuple(2.0f, 1.4f, 3.6f, 0.0f) };
    EXPECT_TRUE(point == vect);
    auto expected{ Tuple::Point(4.0f, 2.8f, 7.2f)};
    auto actual { point + vect };
    EXPECT_FLOAT_EQ(expected.x(), actual.x());
    EXPECT_FLOAT_EQ(expected.y(), actual.y());
    EXPECT_FLOAT_EQ(expected.z(), actual.z());
    EXPECT_FLOAT_EQ(expected.w(), actual.w());
    EXPECT_TRUE(actual.isPoint());
}

TEST(Tuple, Subtraction) {
    auto point{ Tuple(2.0f, 1.4f, 3.6f, 1.0f) };
    auto vect{ Tuple(2.0f, 1.4f, 3.6f, 0.0f) };

    auto expected = Tuple::Point(0.0f, 0.0f, 0.0f);
    auto actual = point - vect;
    EXPECT_FLOAT_EQ(expected.x(), actual.x());
    EXPECT_FLOAT_EQ(expected.y(), actual.y());
    EXPECT_FLOAT_EQ(expected.z(), actual.z());
    EXPECT_FLOAT_EQ(expected.w(), actual.w());
    EXPECT_TRUE(actual.isPoint());

    expected = Tuple::Vector(0.0f, 0.0f, 0.0f);
    actual = vect - vect;
    EXPECT_TRUE(actual.isVector());
}


TEST(Tuple, Negation) {
    auto tuple1{ Tuple(1.0f, -2.0f, 3.0f, -4.0f)};
    auto expected{ Tuple(-1.0f, 2.0f, -3.0f, 4.0f)};
    auto actual{-tuple1};
    EXPECT_TRUE(expected == actual);
}

TEST(Tuple, ScalarMultiplication) {
    auto t{Tuple(1.0f, -2.0f, 3.0f, -4.0f)};
    auto expected{Tuple(3.5f, -7.0f, 10.5f, -14.0f)};
    float scalar = 3.5f;
    float fraction = 0.5;
    auto result{t*scalar};
    EXPECT_FLOAT_EQ(expected.x(), result.x());
    EXPECT_FLOAT_EQ(expected.y(), result.y());
    EXPECT_FLOAT_EQ(expected.z(), result.z());
    EXPECT_FLOAT_EQ(expected.w(), result.w());
    EXPECT_TRUE(result == expected);

    result = t * fraction;
    expected = Tuple(0.5f, -1.0f, 1.5f, -2.0f);
    EXPECT_FLOAT_EQ(expected.x(), result.x());
    EXPECT_FLOAT_EQ(expected.y(), result.y());
    EXPECT_FLOAT_EQ(expected.z(), result.z());
    EXPECT_FLOAT_EQ(expected.w(), result.w());
    EXPECT_TRUE(result == expected);
}

TEST(Tuple, ScalarDivision) {
    auto t{Tuple(1.0f, -2.0f, 3.0f, -4.0f)};
    auto expected{Tuple(0.5f, -1.0f, 1.5f, -2.0f)};
    float scalar = 2.0f;
    auto result{t/scalar};
    EXPECT_FLOAT_EQ(expected.x(), result.x());
    EXPECT_FLOAT_EQ(expected.y(), result.y());
    EXPECT_FLOAT_EQ(expected.z(), result.z());
    EXPECT_FLOAT_EQ(expected.w(), result.w());
    EXPECT_TRUE(result == expected);
}

TEST(Tuple, Magnitude) {
    auto vect { Tuple::Vector(1.0f, 0.0f, 0.0f)};
    auto magnitude = vect.magnitude();
    EXPECT_FLOAT_EQ(magnitude, 1.0f);

    vect = Tuple::Vector(1.0f, 2.0f, 3.0f);
    magnitude = vect.magnitude();
    EXPECT_FLOAT_EQ(magnitude, std::sqrt(14));
}

TEST(Tuple, Normalization) {
    auto vect{Tuple::Vector(4.0f, 0.0f, 0.0f)};
    auto expected{Tuple::Vector(1.0f, 0.0f, 0.0f)};
    auto result{vect.normalize()};
    EXPECT_TRUE(expected == result);

    vect = Tuple::Vector(1.0f, 2.0f, 3.0f);
    expected = Tuple::Vector(1.0f/std::sqrt(14.0f), 2.0f/std::sqrt(14.0f), 3.0f/std::sqrt(14.0f));
    result = vect.normalize();
    EXPECT_TRUE(expected == result);
}

TEST(Tuple, DotProduct) {
    auto a = Tuple::Vector(1.0f, 2.0f, 3.0f);
    auto b = Tuple::Vector(2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(a.dot(b), 20.0f);
}

TEST(Tuple, CrossProduct) {
    auto a = Tuple::Vector(1.0f, 2.0f, 3.0f);
    auto b = Tuple::Vector(2.0f, 3.0f, 4.0f);
    auto expected = Tuple::Vector(-1.0f, 2.0f, -1.0f);
    auto result = a.cross(b);
    EXPECT_TRUE(expected == result);
    expected = Tuple::Vector(1.0f, -2.0f, 1.0f);
    result = b.cross(a);
    EXPECT_TRUE(expected == result);
}
