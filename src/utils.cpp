#include <cmath>

const bool almost_eq(const float lhs, const float rhs, const float epsilon) {
    return std::abs(lhs-rhs) < epsilon;
}
