#pragma once
#include "ray.hpp"
#include "tuple.hpp"
#include <vector>



class Sphere {
private:
    Tuple _origin;
    float _radius;

public:
    Sphere(Tuple origin, float radius):_origin(origin), _radius(radius){};
    std::vector<float> intersections(Ray ray) const;
};
