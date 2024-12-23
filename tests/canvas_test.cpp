#include <sstream>

#include <gtest/gtest.h>
#include <string>
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
    auto expected_ppm_header = "P3\n5 3\n255\n";
    std::string line;
    std::string ppm_header;
    int line_count {0};

    auto ppm = canvas.to_ppm();
    std::istringstream iss{ppm};
    while(std::getline(iss, line) && line_count < 3) {
        ppm_header += line + "\n";
        ++line_count;
    }
    EXPECT_EQ(ppm_header, expected_ppm_header);
}

TEST(CanvasTest, PPMClamping) {
    auto canvas { Canvas(5, 3)};
    auto c1 {Color(1.5f, 0, 0)};
    auto c2 {Color(0, 0.5f, 0)};
    auto c3 {Color(-0.5f, 0, 1.0f)};
    canvas.write_pixel(0, 0, c1);
    canvas.write_pixel(2, 1, c2);
    canvas.write_pixel(4, 2, c3);
    
    std::string line;
    std::string ppm_body;
    std::string ppm {canvas.to_ppm()};
    int line_count { 0 };

    std::istringstream iss{ppm};
    
    while(std::getline(iss, line)) {
        if (line_count >= 3) {
            ppm_body += line + "\n";
        }
        ++line_count;
    }
    
    const std::string expected_ppm_body { "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n"};

    EXPECT_EQ(ppm_body, expected_ppm_body);

}

TEST(CanvasTest, PPMMaxLineLength) {
    auto c { Canvas(10, 2)};
    auto color { Color(1.0f, 0.8f, 0.6f)};
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 2; ++j) {
            c.write_pixel(i, j, color);
        }
    }

    std::string line;
    std::string ppm_body;
    std::string ppm {c.to_ppm()};

    int line_count { 0 };
    std::istringstream iss{ppm};
    while(std::getline(iss, line)) {
        if (line_count >= 3) {
            ppm_body += line + "\n";
        }
        ++line_count;
    }

    const std::string expected_ppm_body {
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"// line break due to line length
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n"// next row
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n" // line break due to line length
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n"};
    EXPECT_EQ(ppm_body, expected_ppm_body);
}

TEST(CanvasTest, PPMEndsWithNewLine) {
    auto c { Canvas(5, 3)};
    auto ppm {c.to_ppm()};
    EXPECT_EQ(ppm.back(), '\n');
}

