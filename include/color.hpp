#pragma once

class Color {
private:
    float _red;
    float _green;
    float _blue;

public:
    Color(float red, float green, float blue): _red(red), _green(green), _blue(blue){};
    float red() const;
    float green() const;
    float blue() const;

};


Color operator+(const Color &lhs, const Color &rhs);
Color operator-(const Color &lhs, const Color &rhs);
Color operator*(const Color &lhs, const float rhs);
Color operator*(const Color &lhs, const Color &rhs);
bool operator==(const Color &lhs, const Color &rhs);
