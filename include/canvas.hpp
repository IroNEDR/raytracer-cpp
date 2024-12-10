#pragma once

#include <vector>
#include "color.hpp"

class Canvas {
private:
    const int _w, _h;
    std::vector<std::vector<Color>> _data;
public:
    Canvas(int w, int h): _w(w), _h(h), _data(w, std::vector<Color>(h,Color(0,0,0))){};
    void write_pixel(int w, int h, Color c);
    int width() const { return _w; }
    int height() const { return _h; }
    Color pixel_at(int w, int h) const;

    std::vector<std::vector<Color>> &data();

};
