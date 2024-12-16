#pragma once

#include <string>
#include <vector>
#include "color.hpp"

class Canvas {
private:
    const int _w, _h;
    std::vector<std::vector<Color>> _data;
public:
    Canvas(int w, int h): _w(w), _h(h), _data(w, std::vector<Color>(h,Color(0,0,0))){};
    void write_pixel(int w, int h,const Color& c);
    int width() const { return _w; }
    int height() const { return _h; }
    Color pixel_at(int w, int h) const;
    std::string to_ppm();

    std::vector<std::vector<Color>> &data();

};

inline int clamp(float color, float min, float max) {
    if (color >= 1.0f) {
        return max;
    } else if (color <= 0.0f) {
        return min;
    } else {
        return std::ceil(color * max);
    }
}
