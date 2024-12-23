#include <gtest/gtest.h>
#include <matrix.hpp>
#include <unistd.h>

TEST(MatrixTest, EmptyInitialization) {
    Matrix<float, 2, 2> m; 
    Matrix<float, 3, 2> n;
    n = {1.0f, 3.4f, 5.1f, 0.0f, 2.0f, 1.4f};

    EXPECT_FLOAT_EQ(m[0][0], 0.0f);
    EXPECT_FLOAT_EQ(n[2][1], 1.4f);
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
