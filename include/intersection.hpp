#pragma once
#include <vector>

template <typename T>
struct Intersection {
    float t;
    T obj;
};

template <typename T>
Intersection<T> hit(std::vector<Intersection<T>> intersections) {
    Intersection<T> hit;
    hit.t = INFINITY;
    for (auto i : intersections) {
        if (i.t > 0 && (i.t < hit.t)) {
            hit = i;
        }
    }
    return hit;
}
