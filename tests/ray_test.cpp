#include <gtest/gtest.h>
#include "ray.hpp"
#include "tuple.hpp"

TEST(Rays, Creation) {
    const auto origin = Tuple::Point(1.0f, 2.0f, 3.0f);
    const auto direction = Tuple::Vector(4.0f, 5.0f, 6.0f); 
    const auto r = Ray(origin, direction);

    EXPECT_TRUE(origin == r.origin());
    EXPECT_TRUE(direction == r.direction());
}


TEST(Rays, Position) {
    const auto origin {Tuple::Point(2.0f, 3.0f, 4.0f)};
    const auto direction {Tuple::Vector(1.0f, 0.0f, 0.0f)};
    const auto ray {Ray(origin, direction)};
    auto position = ray.position(0.0f);
    
    EXPECT_TRUE(position == Tuple::Point(2.0f, 3.0f, 4.0f));
    
    position = ray.position(1.0f);
    EXPECT_TRUE(position == Tuple::Point(3.0f, 3.0f, 4.0f));

    position = ray.position(-1.0f);
    EXPECT_TRUE(position == Tuple::Point(1.0f, 3.0f, 4.0f));

    position = ray.position(2.5f);
    EXPECT_TRUE(position == Tuple::Point(4.5f, 3.0f, 4.0f));
}
