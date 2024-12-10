#include "canvas.hpp"
#include "color.hpp"
#include <vector>


void Canvas::write_pixel(int w, int h, Color c) {
    _data[w][h] = c;
}

Color Canvas::pixel_at(int w, int h) const {
    return _data[w][h];
}

std::vector<std::vector<Color>> &Canvas::data() {
    return _data;
}
