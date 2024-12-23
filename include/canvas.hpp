#pragma once

#include <string>
#include <vector>
#include "color.hpp"

class Canvas {
private:
    const int _w, _h;
    std::vector<std::vector<Color>> _data;
    bool should_split(int color, int body_size); 
public:
    Canvas(int w, int h): _w(w), _h(h), _data(w, std::vector<Color>(h,Color(0,0,0))){};
    void write_pixel(int w, int h,const Color& c);
    int width() const { return _w; }
    int height() const { return _h; }
    Color pixel_at(int w, int h) const;
    const std::string to_ppm();

    std::vector<std::vector<Color>> &data();

};

int clamp(float color, int min, int max);
