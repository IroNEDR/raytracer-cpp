#include "ray.hpp"
#include "tuple.hpp"
#include <stdexcept>

Ray::Ray(Tuple origin, Tuple direction) {
    if(origin.isVector()) {
        throw std::domain_error("error! origin must be a point");
    }
    if(direction.isPoint()) {
        throw std::domain_error("error! direction must be a vector");
    }
    
    _direction = direction;
    _origin = origin;
}


Tuple Ray::origin() const {
    return _origin;
}

Tuple Ray::direction() const {
    return _direction;
}

Tuple Ray::position(float t) const {
    return _origin + (_direction * t);
}
