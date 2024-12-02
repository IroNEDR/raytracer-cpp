#pragma once

const bool almost_eq(const float lhs, const float rhs, const float epsilon);
// helper const that provides a default epsilon. the value should always depend on the context
const float EPSILON = 1.0e-5f;
