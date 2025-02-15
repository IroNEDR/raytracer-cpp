#pragma once
#include "ray.hpp"
#include "tuple.hpp"
#include "intersection.hpp"



class Sphere {
private:
    Tuple _origin;
    float _radius;

public:
    Sphere(Tuple origin, float radius):_origin(origin), _radius(radius){};
    Intersections<Sphere> intersections(Ray ray) const;
    Tuple origin() const { return _origin; }
    float radius() const { return _radius; }
};


bool operator==(const Sphere& lhs, const Sphere& rhs);
bool operator==(Sphere& lhs, Sphere& rhs);
