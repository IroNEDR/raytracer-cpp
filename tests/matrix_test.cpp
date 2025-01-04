#include <gtest/gtest.h>
#include <matrix.hpp>
#include <unistd.h>

TEST(Matrix, EmptyInitialization) {
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

TEST(Matrix, BracketOperator) {
    Matrix<float, 2, 2> m; 
    m = {1.0f, 2.0f, 3.0f, 4.0f};

    EXPECT_FLOAT_EQ(m[0][0], 1.0f);
    EXPECT_FLOAT_EQ(m[1][1], 4.0f);


    m[0][0] = 5.0f;
    m[1][1] = 6.0f;
    EXPECT_FLOAT_EQ(m[0][0], 5.0f);
    EXPECT_FLOAT_EQ(m[1][1], 6.0f);
}


TEST(Matrix, EqualityOperators) {
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


TEST(Matrix, Multiplication) {
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


TEST(Matrix, MultiplicationTuple) {
    Matrix<float, 4, 4> m;
    m = {1.0f,2.0f,3.0f,4.0f,2.0f,4.0f,4.0f,2.0f,8.0f,6.0f,4.0f,1.0f,0.0f,0.0f,0.0f,1.0f};
    Tuple t = Tuple::Point(1.0f, 2.0f, 3.0f);
    Tuple expected = Tuple::Point(18.0f, 24.0f, 33.0f);
    auto result = m * t;
    auto result2 = t * m;
    EXPECT_TRUE(result == expected);
    EXPECT_TRUE(result != result2);
}

TEST(Matrix, IdentityMatrix) {
    Matrix<int,3,3> m;
    m = {1,2,3,4,5,6,7,8,9};
    const auto i = m.identity();
    const auto result = m * i;
    EXPECT_TRUE(result == m);
}


TEST(Matrix, Transpose) {
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


TEST(Matrix, Determinant) {
    Matrix<int,2,2> m;
    m = {1,5,-3,2};
    auto result = m.determinant();
    EXPECT_EQ(result, 17);
    EXPECT_TRUE(m.is_invertible());

    Matrix<int, 3, 3> n;
    n = {1,2,6,-5,8,-4,2,6,4};
    auto result2 = n.determinant();
    EXPECT_EQ(result2, -196);
    EXPECT_TRUE(n.is_invertible());

    Matrix<int, 4, 4> b;
    b = {-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9};
    auto result3 = b.determinant();
    EXPECT_EQ(result3, -4071);
    EXPECT_TRUE(b.is_invertible());

    Matrix<int, 4, 4> c;
    c = {-4, 2, -2, -3, 9, 6, 2, 6, 0, -5, 1, -5, 0, 0, 0, 0};
    auto result4 = c.determinant();
    EXPECT_EQ(result4, 0);
    EXPECT_FALSE(c.is_invertible());
}

TEST(Matrix, Submatrix) {
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


TEST(Matrix, Minor) {
    Matrix<int,3,3> m;
    m = {3,5,0,2,-2,-7,6,-1,5};
    const auto result = m.minor(1, 0);
    EXPECT_EQ(result, 25);
}


TEST(Matrix, Cofactor) {
    Matrix<int,3,3> m;
    m = {3,5,0,2,-1,-7,6,-1,5};
    auto result = m.cofactor(0, 0);
    EXPECT_EQ(result, -12);
    result = m.cofactor(1, 0);
    EXPECT_EQ(result, -25);

    Matrix<int, 3, 3> n;
    n = {1,2,6,-5,8,-4,2,6,4};
    result = n.cofactor(0, 1);
    EXPECT_EQ(result, 12);

    result = n.cofactor(0, 2);
    EXPECT_EQ(result, -46);
    result = n.cofactor(0, 1);
    EXPECT_EQ(result, 12);

    Matrix<int, 4, 4> b;
    b = {-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9};
    result = b.cofactor(0, 0);
    EXPECT_EQ(result, 690);
    result = b.cofactor(0, 1);
    EXPECT_EQ(result, 447);
    result = b.cofactor(0, 2);
    EXPECT_EQ(result, 210);
    result = b.cofactor(0, 3);
    EXPECT_EQ(result, 51);
}


TEST(Matrix, Inverse) {
    Matrix<float, 4, 4> m;
    m = { 
        -5.0f, 2.0f, 6.0f, -8.0f,
        1.0f, -5.0f, 1.0f, 8.0f,
        7.0f, 7.0f, -6.0f, -7.0f,
        1.0f, -3.0f, 7.0f, 4.0f
    };
    
    const auto det = m.determinant();
    EXPECT_FLOAT_EQ(det, 532.0f);
    
    auto cof = m.cofactor(2, 3);
    EXPECT_FLOAT_EQ(cof, -160.0f);
    
    const auto inv = m.inverse();
    EXPECT_FLOAT_EQ(inv[3][2], -160.0f/532.0f);
    
    cof = m.cofactor(3, 2);
    
    EXPECT_FLOAT_EQ(105.0f, cof);
    EXPECT_FLOAT_EQ(inv[2][3], 105.0f/532.0f);
    
    Matrix<float,4,4> inv_expect;

    inv_expect = {
         0.21805,  0.45113,  0.24060, -0.04511,
        -0.80827, -1.45677, -0.44361, 0.52068,
        -0.07895, -0.22368, -0.05263, 0.19737,
        -0.52256, -0.81391, -0.30075, 0.30639
    };

    EXPECT_TRUE(inv == inv_expect);


    Matrix<int, 4,4> n;
    n = {8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4};
    const auto inv2 = n.inverse();
    Matrix<float, 4,4> inv_expect2;
    inv_expect2 = {
        -0.15385f, -0.15385f, -0.28205f, -0.53846f,
        -0.07692f, 0.12308f, 0.02564f, 0.03077f,
        0.35897f, 0.35897f, 0.43590f, 0.92308f,
        -0.69231f, -0.69231f, -0.76923f, -1.92308f
    };


    EXPECT_TRUE(inv2 == inv_expect2);


    Matrix<int, 4,4> o;
    o = {9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2};
    const auto inv3 = o.inverse();
    Matrix<float, 4,4> inv_expect3;
    inv_expect3 = {
        -0.04074f, -0.07778f, 0.14444f, -0.22222f,
        -0.07778f, 0.03333f, 0.36667f, -0.33333f,
        -0.02901f, -0.14630f, -0.10926f, 0.12963f,
        0.17778f, 0.06667, -0.26667f, 0.33333f
    };

    EXPECT_TRUE(inv3 == inv_expect3);

    Matrix<int, 4,4> p;
    p = {3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1};
    Matrix<int,4,4> b;
    b ={ 8, 2,2,2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5};
    const auto c = p * b;
    const auto d = c * b.inverse();
    EXPECT_TRUE(d == p);

}
