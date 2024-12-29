#include <gtest/gtest.h>
#include <matrix.hpp>
#include <unistd.h>

TEST(MatrixTest, EmptyInitialization) {
    Matrix<float, 2, 2> m; 
    Matrix<float, 3, 2> n;
    n = {1.0f, 3.4f, 5.1f, 0.0f, 2.0f, 1.4f};
    EXPECT_FLOAT_EQ(m[0][0], 0.0f);
    EXPECT_FLOAT_EQ(n[2][1], 1.4f);
    constexpr int rows = n.rows();
    constexpr int cols = n.cols();
    EXPECT_EQ(rows, 3);
    EXPECT_EQ(cols, 2);
}

TEST(MatrixTest, BracketOperator) {
    Matrix<float, 2, 2> m; 
    m = {1.0f, 2.0f, 3.0f, 4.0f};

    EXPECT_FLOAT_EQ(m[0][0], 1.0f);
    EXPECT_FLOAT_EQ(m[1][1], 4.0f);


    m[0][0] = 5.0f;
    m[1][1] = 6.0f;
    EXPECT_FLOAT_EQ(m[0][0], 5.0f);
    EXPECT_FLOAT_EQ(m[1][1], 6.0f);
}


TEST(MatrixTest, EqualityOperators) {
    Matrix<int, 3, 3> m;
    Matrix<int, 3, 3> n;
    Matrix<float, 3, 3> p;
    Matrix<float, 3, 3> q;
    m = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    n = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    p = {1.0f, 2.0f, 3.0f,
         4.0f, 5.0f, 6.0f,
         7.0f, 8.0f, 9.0f };

    q = {1.1f, 2.2f, 3.0f,
         4.0f, 5.0f, 6.0f,
         7.0f, 8.0f, 9.0f };

    EXPECT_TRUE(m == n);
    EXPECT_FALSE(m != n);
    EXPECT_FALSE(p == q);
    EXPECT_TRUE(p != q);
}


TEST(MatrixTest, Multiplication) {
    Matrix<int, 4, 4> m;
    Matrix<int, 4, 4> n;
    Matrix<int, 4, 3> x;
    Matrix<int, 3, 3> y;
    Matrix<int, 4, 4> expected;
    Matrix<int, 4, 3> expected2;
    m = {1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2};
    n = {-2,1,2,3,3,2,1,-1,4,3,6,5,1,2,7,8};
    x = {1,0,1,2,1,1,0,1,1,1,1,2};
    y = {1,2,1,2,3,1,4,2,2};
    expected = {20,22,50,48,44,54,114,108,40,58,110,102,16,26,46,42};
    expected2 = {5,4,3,8,9,5,6,5,3,11,9,6};
    auto actual = m * n;
    auto actual2 = x * y;
    EXPECT_TRUE(actual == expected);
    EXPECT_TRUE(actual2 == expected2);
}


TEST(MatrixTest, MultiplicationWithTuple) {
    Matrix<float, 4, 4> m;
    m = {1.0f,2.0f,3.0f,4.0f,2.0f,4.0f,4.0f,2.0f,8.0f,6.0f,4.0f,1.0f,0.0f,0.0f,0.0f,1.0f};
    Tuple t = Tuple::Point(1.0f, 2.0f, 3.0f);
    Tuple expected = Tuple::Point(18.0f, 24.0f, 33.0f);
    auto result = m * t;

    EXPECT_TRUE(result == expected);
}

TEST(MatrixTest, IdentityMatrix) {
    Matrix<int,3,3> m;
    m = {1,2,3,4,5,6,7,8,9};
    const auto i = m.identity();
    const auto result = m * i;
    EXPECT_TRUE(result == m);
}


TEST(MatrixTest, Transpose) {
    Matrix<int,2,2> m;
    m = {1,2,3,4};
    const auto result = m.transpose();
    Matrix<int,2,2> expected;
    expected = {1,3,2,4};

    EXPECT_TRUE(result == expected);

    Matrix<int,3,2> n;
    n = {1,2,3,4,5,6};
    const auto result2 = n.transpose();
    Matrix<int,2,3> expected2;
    expected2 = {1,3,5,2,4,6};
    EXPECT_TRUE(result2 == expected2);

    Matrix<int,1,2> o;
    o = {1,2};
    const auto result3 = o.transpose();
    Matrix<int,2,1> expected3;
    expected3 = {1,2};
    EXPECT_TRUE(result3 == expected3);

    Matrix<int, 4,4> p;
    p = {0,9,3,0,9,8,0,8,1,8,5,3,0,0,5,8};
    const auto result4 = p.transpose();
    Matrix<int, 4,4> expected4;
    expected4 = {0,9,1,0,9,8,8,0,3,0,5,5,0,8,3,8};
    EXPECT_TRUE(result4 == expected4);
    const auto i = p.identity();
    const auto result5 = i.transpose();
    EXPECT_TRUE(result5 == i);
}


TEST(MatrixTest, Determinant) {
    Matrix<int,2,2> m;
    m = {1,5,-3,2};
    const auto result = m.determinant();
    EXPECT_EQ(result, 17);
}

TEST(MatrixTest, Submatrix) {
    Matrix<int,3,3> m;
    m = { 1, 5, 0, -3, 2, 7, 0, 6, -3};
    const auto result = m.submatrix(0, 2);
    Matrix<int,2,2> expected;
    expected = {-3, 2, 0, 6};
    EXPECT_TRUE(result == expected);

    Matrix<int,4,4> n;
    n = {-6,1,1,6, -8,5,8,6, -1,0,8,2, -7,1,-1,1};
    const auto result2 = n.submatrix(2, 1);
    Matrix<int,3,3> expected2;
    expected2 = {-6,1,6, -8,8,6, -7,-1,1};
    EXPECT_TRUE(result2 == expected2);
}


TEST(MatrixTest, Minor) {
    Matrix<int,3,3> m;
    m = {3,5,0,2,-2,-7,6,-1,5};
    const auto result = m.minor(1, 0);
    EXPECT_EQ(result, 25);
}
