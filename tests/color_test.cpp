#include <gtest/gtest.h>
#include <color.hpp>


TEST(ColorTest, Creation) {
    const auto c{Color(-0.5f, 0.4f, 1.7f)};
    EXPECT_FLOAT_EQ(c.red(), -0.5f);
    EXPECT_FLOAT_EQ(c.green(), 0.4f);
    EXPECT_FLOAT_EQ(c.blue(), 1.7f);
}


TEST(ColorTest, Addition) {
    const auto c1{Color(0.9f, 0.6f, 0.75f)};
    const auto c2{Color(0.7f, 0.1f, 0.25f)};
    const auto result {c1 + c2};
    EXPECT_FLOAT_EQ(result.red(), 1.6f);
    EXPECT_FLOAT_EQ(result.green(), 0.7f);
    EXPECT_FLOAT_EQ(result.blue(), 1.0f);
}

TEST(ColorTest, Subtraction) {
    const auto c1{Color(0.9f, 0.6f, 0.75f)};
    const auto c2{Color(0.7f, 0.1f, 0.25f)};
    const auto result {c1 - c2};
    EXPECT_FLOAT_EQ(result.red(), 0.2f);
    EXPECT_FLOAT_EQ(result.green(), 0.5f);
    EXPECT_FLOAT_EQ(result.blue(), 0.5f);
}

TEST(ColorTest, ScalarMultiplication) {
    const auto c{Color(0.2f, 0.3f, 0.4f)};
    const auto result {c * 2.0f};
    EXPECT_FLOAT_EQ(result.red(), 0.4f);
    EXPECT_FLOAT_EQ(result.green(), 0.6f);
    EXPECT_FLOAT_EQ(result.blue(), 0.8f);
}

TEST(ColorTest, HadamardProduct) {
    const auto c1{Color(1.0f, 0.2f, 0.4f)};
    const auto c2{Color(0.9f, 1.0f, 0.1f)};
    const auto result {c1 * c2};
    EXPECT_FLOAT_EQ(result.red(), 0.9f);
    EXPECT_FLOAT_EQ(result.green(), 0.2f);
    EXPECT_FLOAT_EQ(result.blue(), 0.04f);
}
