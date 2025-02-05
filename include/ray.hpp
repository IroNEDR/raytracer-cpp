#pragma once
#include "tuple.hpp"

class Ray {

private:
    Tuple _origin;
    Tuple _direction;

public:
    Ray(Tuple origin, Tuple direction);
    Ray() = default;
    
    Tuple origin() const;
    Tuple direction() const;
    Tuple position(float t) const;

};
