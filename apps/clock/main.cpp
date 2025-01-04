#include "transform.hpp"
#include "tuple.hpp"
#include "canvas.hpp"
#include <ctime>
#include <format>
#include <fstream>
#include <numbers>
#include <iostream>



int main() {
    auto canvas {Canvas(600,600)};
    auto current_time {Tuple::Point(0.0f, 0.0f, 1.0f)};
    const float radius = 600 * (3.0f/8.0f);
    std::cout << std::format("radius: {}\n", radius);
    const auto scaling_matrix {transformations::scaling_matrix(radius, 0.0f, radius)};
    const auto translation_matrix {transformations::translation_matrix(300.0f, 0.0f, 300.0f)};
    
    const auto rotation_matrix {transformations::rotation_y_matrix(std::numbers::pi/6)};
    for(int i = 0; i < 12; ++i ) {
        current_time = rotation_matrix * current_time;
        auto scaled_current_time = scaling_matrix * current_time;
        auto centered_current_time = translation_matrix * scaled_current_time;
        canvas.write_pixel(centered_current_time.x(), centered_current_time.z(), Color(1.0f, 0.0f, 0.0f));
    }

    auto ppm = canvas.to_ppm();
    std::ofstream outfile {"clock.ppm"}; 
    outfile << ppm;

    return 0;
}
