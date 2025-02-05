#include <gtest/gtest.h>
#include "sphere.hpp"
#include "ray.hpp"


TEST(Sphere, TwoPointIntersection) {
    const auto r = Ray(Tuple::Point(0.0f, 0.0f, -5.0f), Tuple::Vector(0.0f, 0.0f, 1.0f));
    const auto s = Sphere(Tuple::Point(0.0f, 0.0f, 0.0f), 1.0f);
    const auto xs = s.intersections(r);
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0], 4.0f);
    EXPECT_FLOAT_EQ(xs[1], 6.0f);
}

TEST(Sphere, OnePointIntersection) {
    const auto r = Ray(Tuple::Point(0.0f, 1.0f, -5.0f), Tuple::Vector(0.0f, 0.0f, 1.0f));
    const auto s = Sphere(Tuple::Point(0.0f, 0.0f, 0.0f), 1.0f);
    const auto xs = s.intersections(r);
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0], 5.0f);
    EXPECT_FLOAT_EQ(xs[1], 5.0f);
}

TEST(Sphere, NoIntersection) {
    const auto r = Ray(Tuple::Point(0.0f, 2.0f, -5.0f), Tuple::Vector(0.0f, 0.0f, 1.0f));
    const auto s = Sphere(Tuple::Point(0.0f, 0.0f, 0.0f), 1.0f);
    const auto xs = s.intersections(r);
    ASSERT_EQ(xs.size(), 0);
}

TEST(Sphere, InsideIntersection) {
    const auto r = Ray(Tuple::Point(0.0f, 0.0f, 0.0f), Tuple::Vector(0.0f, 0.0f, 1.0f));
    const auto s = Sphere(Tuple::Point(0.0f, 0.0f, 0.0f), 1.0f);
    const auto xs = s.intersections(r);
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0], -1.0f);
    EXPECT_FLOAT_EQ(xs[1], 1.0f);
}

TEST(Sphere, BehindRayIntersection) {
    const auto r = Ray(Tuple::Point(0.0f, 0.0f, 5.0f), Tuple::Vector(0.0f, 0.0f, 1.0f));
    const auto s = Sphere(Tuple::Point(0.0f, 0.0f, 0.0f), 1.0f);
    const auto xs = s.intersections(r);
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0], -6.0f);
    EXPECT_FLOAT_EQ(xs[1], -4.0f);
}
