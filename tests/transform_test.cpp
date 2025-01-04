#include <cmath>
#include <gtest/gtest.h>
#include <numbers>
#include "transform.hpp"
#include "tuple.hpp"

TEST(Transformation, TranslatePoint) {
    const auto transformation_matrix {transformations::translation_matrix(5.0f, -3.0f, 2.0f)};
    const auto inv = transformation_matrix.inverse();
    const auto expected {Tuple::Point(-8.0f, 7.0f, 3.0f)};
    const auto result = inv * Tuple::Point(-3.0f, 4.0f, 5.0f);

    EXPECT_TRUE(result == expected);
}


TEST(Transformation, TranslateVector) {
    const auto transformation_matrix {transformations::translation_matrix(5.0f, -3.0f, 2.0f)};
    const auto vector {Tuple::Vector(-3.0f, 4.0f, 5.0f)};
    const auto result =  vector * transformation_matrix;
    // due to the 0 in its w component, the vector is not affected by translation
    EXPECT_TRUE(result == vector);
}


TEST(Transformation, ScalingMatrix) {
    const auto transformation_matrix {transformations::scaling_matrix(2.0f, 3.0f, 4.0f)};
    const auto point {Tuple::Point(-4.0f, 6.0f, 8.0f)};
    const auto result =  transformation_matrix * point;
    const auto expected {Tuple::Point(-8.0f, 18.0f, 32.0f)};
    EXPECT_TRUE(result == expected);
}

TEST(Transformation, ScalingVector) {
    const auto transformation_matrix {transformations::scaling_matrix(2.0f, 3.0f, 4.0f)};
    const auto vector {Tuple::Vector(-4.0f, 6.0f, 8.0f)};
    const auto result =  transformation_matrix.inverse() * vector;
    const auto expected {Tuple::Vector(-2.0f, 2.0f, 2.0f)};
    EXPECT_TRUE(result == expected);
}


TEST(Transformation, Reflection) {
    const auto transformation_matrix {transformations::scaling_matrix(-1.0f, 1.0f, 1.0f)};
    const auto point {Tuple::Point(2.0f, 3.0f, 4.0f)};
    const auto result =  transformation_matrix * point;
    const auto expected {Tuple::Point(-2.0f, 3.0f, 4.0f)};
    EXPECT_TRUE(result == expected);
}

TEST(Transformation, RotationX) {
    const auto point {Tuple::Point(0.0f, 1.0f, 0.0f)};
    const auto half_quarter_matrix = transformations::rotation_x_matrix(std::numbers::pi/4);
    const auto full_quarter_matrix = transformations::rotation_x_matrix(std::numbers::pi/2);
    const auto half_quarter_result = half_quarter_matrix * point;
    const auto full_quarter_result = full_quarter_matrix * point;
    const auto half_quarter_expect {Tuple::Point(0.0f, std::sqrt(2)/2, std::sqrt(2)/2)};
    const auto full_quarter_expect {Tuple::Point(0.0f, 0.0f, 1.0f)};
    EXPECT_TRUE(half_quarter_result == half_quarter_expect);
    EXPECT_TRUE(full_quarter_result == full_quarter_expect);
}

TEST(Transformation, RotationY) {
    const auto point {Tuple::Point(0.0f, 0.0f, 1.0f)};
    const auto half_quarter_matrix = transformations::rotation_y_matrix(std::numbers::pi/4);
    const auto full_quarter_matrix = transformations::rotation_y_matrix(std::numbers::pi/2);
    const auto half_quarter_result = half_quarter_matrix * point;
    const auto full_quarter_result = full_quarter_matrix * point;
    const auto half_quarter_expect {Tuple::Point(std::sqrt(2)/2, 0.0f, std::sqrt(2)/2)};
    const auto full_quarter_expect {Tuple::Point(1.0f, 0.0f, 0.0f)};
    EXPECT_TRUE(half_quarter_result == half_quarter_expect);
    EXPECT_TRUE(full_quarter_result == full_quarter_expect);
}

TEST(Transformation, RotationZ) {
    const auto point {Tuple::Point(0.0f, 1.0f, 0.0f)};
    const auto half_quarter_matrix = transformations::rotation_z_matrix(std::numbers::pi/4);
    const auto full_quarter_matrix = transformations::rotation_z_matrix(std::numbers::pi/2);
    const auto half_quarter_result = half_quarter_matrix * point;
    const auto full_quarter_result = full_quarter_matrix * point;
    const auto half_quarter_expect {Tuple::Point(-std::sqrt(2)/2, std::sqrt(2)/2, 0.0f)};
    const auto full_quarter_expect {Tuple::Point(-1.0f, 0.0f, 0.0f)};
    EXPECT_TRUE(half_quarter_result == half_quarter_expect);
    EXPECT_TRUE(full_quarter_result == full_quarter_expect);
}

TEST(Transformation, Shearing) {
    const auto transformation_matrix_xy = transformations::shearing_matrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    const auto point = Tuple::Point(2.0f, 3.0f, 4.0f);
    const auto result_xy = transformation_matrix_xy * point;
    auto expected = Tuple::Point(5.0f, 3.0f, 4.0f);
    EXPECT_TRUE(result_xy == expected);

    const auto transformation_matrix_xz = transformations::shearing_matrix(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    const auto result_xz = transformation_matrix_xz * point;
    expected = Tuple::Point(6.0f, 3.0f, 4.0f);
    EXPECT_TRUE(result_xz == expected);

    const auto transformation_matrix_yx = transformations::shearing_matrix(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
    const auto result_yx = transformation_matrix_yx * point;
    expected = Tuple::Point(2.0f, 5.0f, 4.0f);
    EXPECT_TRUE(result_yx == expected);

    const auto transformation_matrix_yz = transformations::shearing_matrix(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    const auto result_yz = transformation_matrix_yz * point;
    expected = Tuple::Point(2.0f, 7.0f, 4.0f);
    EXPECT_TRUE(result_yz == expected);

    const auto transformation_matrix_zx = transformations::shearing_matrix(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    const auto result_zx = transformation_matrix_zx * point;
    expected = Tuple::Point(2.0f, 3.0f, 6.0f);
    EXPECT_TRUE(result_zx == expected);

    const auto transformation_matrix_zy = transformations::shearing_matrix(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    const auto result_zy = transformation_matrix_zy * point;
    expected = Tuple::Point(2.0f, 3.0f, 7.0f);
    EXPECT_TRUE(result_zy == expected);
}

TEST(Transformation, Chaining) {
    const auto point = Tuple::Point(1.0f, 0.0f, 1.0f);
    const auto A = transformations::rotation_x_matrix(std::numbers::pi/2);
    const auto B = transformations::scaling_matrix(5.0f, 5.0f, 5.0f);
    const auto C = transformations::translation_matrix(10.0f, 5.0f, 7.0f);
    auto result = A * point;
    const auto expected = Tuple::Point(1.0f, -1.0f, 0.0f);
    EXPECT_TRUE(result == expected);

    result = B * result;
    const auto expected2 = Tuple::Point(5.0f, -5.0f, 0.0f);
    EXPECT_TRUE(result == expected2);

    result = C * result;
    const auto expected3 = Tuple::Point(15.0f, 0.0f, 7.0f);
    EXPECT_TRUE(result == expected3);

    const auto transformation = C*B*A;
    result = transformation * point;
    EXPECT_TRUE(result == expected3);

}
