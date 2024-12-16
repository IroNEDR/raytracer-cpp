#include "canvas.hpp"
#include "color.hpp"
#include <format>
#include <vector>


void Canvas::write_pixel(int w, int h, const Color& c) {
    _data[w][h] = c;
}

Color Canvas::pixel_at(int w, int h) const {
    return _data[w][h];
}

std::vector<std::vector<Color>> &Canvas::data() {
    return _data;
}

std::string Canvas::to_ppm() {
    auto header = std::format("P3\n{} {}\n255\n", _w, _h);
    auto body = std::string();
    for(int i = 0; i < _h; i++) {
        for(int j = 0; j < _w; j++) {
            body += std::format("{} {} {}", clamp(_data[i][j].red(), 0, 255),
                                clamp(_data[i][j].green(), 0, 255),
                                clamp(_data[i][j].blue(), 0, 255));
            if(j < _w - 1) {
                body += " ";
            }
        }
        body += "\n";
    }
    return header + body;
}
