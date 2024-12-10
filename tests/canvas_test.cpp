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
