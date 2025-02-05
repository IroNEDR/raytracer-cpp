#include "sphere.hpp"
#include "ray.hpp"


std::vector<float> Sphere::intersections(Ray ray) const {
    // Ray intersections t1, t2 with sphere
    // Ray(t1) = origin + t1 * direction
    // ||t - Sphere_Center||^2 = r^2
    // For t1:
    // ||origin + t1 * direction - Sphere_Center||^2 = r^2
    const auto sphere_to_ray = ray.origin() - _origin;
    auto a = ray.direction().dot(ray.direction());
    auto b = 2 * ray.direction().dot(sphere_to_ray);
    auto c = sphere_to_ray.dot(sphere_to_ray) - 1;

    auto discriminant = b*b - 4 * a * c;
    if(discriminant < 0) {
        return std::vector<float>{};
    }
    auto t1 = (-b - sqrt(discriminant)) / (2 * a);
    auto t2 = (-b + sqrt(discriminant)) / (2 * a);

    return std::vector<float>{t1, t2};
}
