#pragma once

#include "matrix.hpp"

namespace transformations {
    Matrix<float,4,4> translation_matrix(float x, float y, float z);
    Matrix<float,4,4> scaling_matrix(float x, float y, float z);
    Matrix<float,4,4> rotation_x_matrix(float radians);
    Matrix<float,4,4> rotation_y_matrix(float radians);
    Matrix<float,4,4> rotation_z_matrix(float radians);
    Matrix<float,4,4> shearing_matrix(float xy, float xz, float yx, float yz, float zx, float zy);
}
