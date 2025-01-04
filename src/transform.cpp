#include "transform.hpp"
#include "matrix.hpp"
#include <cmath>

namespace transformations {
    Matrix<float,4,4> scaling_matrix(float x, float y, float z) {
        auto m = Matrix<float,4,4>().identity();
        m[0][0] = x;
        m[1][1] = y;
        m[2][2] = z;
        return m;
    }

    Matrix<float,4,4> translation_matrix(float x, float y, float z) {
        auto m = Matrix<float,4,4>().identity();
        m[0][3] = x;
        m[1][3] = y;
        m[2][3] = z;
        return m;
    };

    Matrix<float,4,4> rotation_x_matrix(float radians) {
        const auto sinr = std::sin(radians);
        const auto cosr = std::cos(radians);
        Matrix<float,4,4> m;
        m[0][0] = 1;
        m[1][1] = cosr;
        m[1][2] = -sinr;
        m[2][1] = sinr;
        m[3][2] = cosr;
        m[3][3] = 1;
        return m;
    }

    Matrix<float,4,4> rotation_y_matrix(float radians) {
        const auto sinr = std::sin(radians);
        const auto cosr = std::cos(radians);
        Matrix<float,4,4> m;
        m[0][0] = cosr;
        m[0][2] = sinr;
        m[1][1] = 1.0f;
        m[2][0] = -sinr;
        m[2][2] = cosr;
        m[3][3] = 1.0f;
        return m;
    }

    Matrix<float,4,4> rotation_z_matrix(float radians) {
        const auto sinr = std::sin(radians);
        const auto cosr = std::cos(radians);
        Matrix<float,4,4> m;
        m[0][0] = cosr;
        m[0][1] = -sinr;
        m[1][0] = sinr;
        m[1][1] = cosr;
        m[2][2] = 1.0f;
        m[3][3] = 1.0f;
        return m;
    }

    Matrix<float,4,4> shearing_matrix(float xy, float xz, float yx, float yz, float zx, float zy) {
        Matrix<float,4,4> m;
        m[0][0] = 1.0f;
        m[0][1] = xy;
        m[0][2] = xz;
        m[1][0] = yx;
        m[1][1] = 1.0f;
        m[1][2] = yz;
        m[2][0] = zx;
        m[2][1] = zy;
        m[2][2] = 1.0f;
        m[3][3] = 1.0f;
        return m;
    }

}
