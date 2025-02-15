#include "sphere.hpp"
#include "intersection.hpp"
#include "ray.hpp"
#include "utils.hpp"


Intersections<Sphere> Sphere::intersections(Ray ray) const {
    const auto sphere_to_ray = ray.origin() - _origin;
    auto a = ray.direction().dot(ray.direction());
    auto b = 2 * ray.direction().dot(sphere_to_ray);
    auto c = sphere_to_ray.dot(sphere_to_ray) - 1;

    auto discriminant = b*b - 4 * a * c;
    if(discriminant < 0) {
        return Intersections<Sphere>{};
    }
    auto t1 = (-b - sqrt(discriminant)) / (2 * a);
    auto t2 = (-b + sqrt(discriminant)) / (2 * a);
    Intersection<Sphere> t1_intersection(t1, *this);
    Intersection<Sphere> t2_intersection(t2, *this);

    return Intersections<Sphere>{t1_intersection, t2_intersection};
}


bool operator==(const Sphere& lhs, const Sphere& rhs) {
    return lhs.origin() == rhs.origin() && almost_eq(lhs.radius(), rhs.radius(), EPSILON);
}


bool operator==(Sphere& lhs, Sphere& rhs) {
    return lhs.origin() == rhs.origin() && almost_eq(lhs.radius(), rhs.radius(), EPSILON);
}
