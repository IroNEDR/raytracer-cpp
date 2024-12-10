#include "tuple.hpp"
#include "utils.hpp"
#include <cmath>

Tuple Tuple::Point(const float x, const float y, const float z) {
    return Tuple(x,y,z,1.0f);
}

Tuple Tuple::Vector(const float x, const float y, const float z) {
    return Tuple(x,y,z,0.0f);
}

bool Tuple::isPoint() const {
    return _w == 1.0;
}

bool Tuple::isVector() const {
    return _w == 0.0;
}

float Tuple::magnitude() const {
    return std::sqrt(_x*_x + _y * _y + _z * _z + _w * _w);
}

float Tuple::dot(const Tuple t) const {
    return _x * t.x() + _y * t.y() + _z * t.z() + _w * t._w;
}

Tuple Tuple::cross(const Tuple t) const {
    return Tuple::Vector(
        _y*t.z() - _z * t.y(),
        _z * t.x() - _x * t.z(),
        _x * t.y() - _y * t.x()
    );
}

Tuple Tuple::normalize() const {
    return Tuple(_x / this->magnitude(), _y / this->magnitude(),
                 _z / this->magnitude(), _w / this->magnitude());
}


bool operator==(const Tuple &lhs, const Tuple &rhs) {
    return almost_eq(lhs.x(), rhs.x(), EPSILON) &&
        almost_eq(lhs.y(), rhs.y(), EPSILON) &&
        almost_eq(lhs.z(), rhs.z(), EPSILON);
}

Tuple operator+(const Tuple &lhs, const Tuple &rhs) {
    return Tuple(lhs.x() + rhs.x(), lhs.y() + rhs.y(),
                 lhs.z() + rhs.z(), lhs.w() + rhs.w()); 
}

Tuple operator-(const Tuple &lhs, const Tuple &rhs) {
    return Tuple(lhs.x() - rhs.x(), lhs.y() - rhs.y(),
                 lhs.z() - rhs.z(), lhs.w() - rhs.w());
}

Tuple operator-(const Tuple &t) {
    return Tuple(-t.x(), -t.y(), -t.z(), -t.w());
}

Tuple operator*(const Tuple &lhs, float s) {
    return Tuple(lhs.x()*s, lhs.y()*s, lhs.z()*s, lhs.w()*s);
}

Tuple operator/(const Tuple &lhs, float d) {
    return Tuple(lhs.x()/d, lhs.y()/d, lhs.z()/d, lhs.w()/d);
}
