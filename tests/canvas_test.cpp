#include <gtest/gtest.h>
#include "color.hpp"
#include "canvas.hpp"


TEST(CanvasTest, Creation) {
    auto canvas { Canvas(10, 20)};
    auto w = canvas.width();
    auto h = canvas.height();
    EXPECT_EQ(w, 10);
    EXPECT_EQ(h, 20);
    auto expected_color {Color(0, 0, 0)};
    auto data = canvas.data();
    for(auto &rows : data ) {
        for(auto &pixel : rows) {
            EXPECT_TRUE(pixel == expected_color);
        }
    }
}


TEST(CanvasTest, WritePixel) {
    auto canvas { Canvas(10, 20)};
    auto red { Color(1.0f, 0.0f, 0.0f)};
    canvas.write_pixel(2, 3, red);
    auto expected_color = canvas.pixel_at(2, 3);
    EXPECT_TRUE(expected_color == red);
}


TEST(CanvasTest, ToPPM) {
    auto canvas { Canvas(5, 3)};
    auto ppm = canvas.to_ppm();
    auto expected_ppm = "P3\n5 3\n255\n";
    EXPECT_EQ(ppm.substr(0, 11), expected_ppm);
}
