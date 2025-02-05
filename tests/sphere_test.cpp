#include <gtest/gtest.h>
#include "sphere.hpp"
#include "ray.hpp"


TEST(Sphere, TwoPointIntersection) {
    const auto r = Ray(Tuple::Point(0.0f, 0.0f, -5.0f), Tuple::Vector(0.0f, 0.0f, 1.0f));
    const auto s = Sphere(Tuple::Point(0.0f, 0.0f, 0.0f), 1.0f);
    const auto xs = s.intersections(r);
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 4.0f);
    EXPECT_FLOAT_EQ(xs[1].t, 6.0f);
    EXPECT_TRUE(xs[0].obj == s);
    EXPECT_EQ(xs[1].obj, s);
}

TEST(Sphere, OnePointIntersection) {
    const auto r = Ray(Tuple::Point(0.0f, 1.0f, -5.0f), Tuple::Vector(0.0f, 0.0f, 1.0f));
    const auto s = Sphere(Tuple::Point(0.0f, 0.0f, 0.0f), 1.0f);
    const auto xs = s.intersections(r);
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 5.0f);
    EXPECT_FLOAT_EQ(xs[1].t, 5.0f);
    EXPECT_EQ(xs[0].obj, s);
    EXPECT_EQ(xs[1].obj, s);
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
    EXPECT_FLOAT_EQ(xs[0].t, -1.0f);
    EXPECT_FLOAT_EQ(xs[1].t, 1.0f);
    EXPECT_EQ(xs[0].obj, s);
    EXPECT_EQ(xs[1].obj, s);
}

TEST(Sphere, BehindRayIntersection) {
    const auto r = Ray(Tuple::Point(0.0f, 0.0f, 5.0f), Tuple::Vector(0.0f, 0.0f, 1.0f));
    const auto s = Sphere(Tuple::Point(0.0f, 0.0f, 0.0f), 1.0f);
    const auto xs = s.intersections(r);
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, -6.0f);
    EXPECT_FLOAT_EQ(xs[1].t, -4.0f);
    EXPECT_EQ(xs[0].obj, s);
    EXPECT_EQ(xs[1].obj, s);
}
