#include "canvas.hpp"
#include "color.hpp"
#include <format>
#include <math.h>

void Canvas::write_pixel(int w, int h, const Color& c) {
    if (w >= _w || h >= _h) {
        throw std::out_of_range("Canvas index out of bounds");
    }
    _data[w][h] = c;
}
Color Canvas::pixel_at(int w, int h) const {
    if (w >= _w || h >= _h) {
        throw std::out_of_range("Canvas index out of bounds");
    }
    return _data[w][h];
}

std::vector<std::vector<Color>> &Canvas::data() {
    return _data;
}

bool Canvas::should_split(int color, int line_length) {
    int col_length {0};
    int max_line_length {70};
    if (color > 99 ) {
        col_length = 3;
    } else if (color < 10) {
        col_length = 1;
    } else {
        col_length = 2;
    }
    if (col_length + line_length >= max_line_length) {
        return true;
    }
    return false;
}

const std::string Canvas::to_ppm() {
    auto header = std::format("P3\n{} {}\n255\n", _w, _h);
    auto body = std::string();
    for(int i = 0; i < _h; ++i) {
        auto line = std::string();
        line.clear();
        for(int j = 0; j < _w; ++j) {
            auto red = clamp(_data[j][i].red(), 0, 255);
            auto green = clamp(_data[j][i].green(), 0, 255);
            auto blue = clamp(_data[j][i].blue(), 0, 255);
            if (this->should_split(red, line.length())) {
                line += "\n";
                body += line;
                line.clear();
            } else if (line.length() > 0) {
                line += " ";
            }
            line += std::format("{}",red);
            if (this->should_split(green, line.length())) {
                line += "\n";
                body += line;
                line.clear();
            } else if (line.length() > 0) {
                line += " ";
            }
            line += std::format("{}",green);
            if (this->should_split(blue, line.length())) {
                line += "\n";
                body += line;
                line.clear();
            } else if (line.length() > 0) {
                line += " ";
            }
            line += std::format("{}",blue);
        }
        line += "\n";
        body += line;
    }
    return header + body;
}

int clamp(float color, int min, int max) {
    if (color >= 1.0f) {
        return max;
    } else if (color < 0.0f) {
        return min;
    } else {
        return ceil(color * max);
    }
}
