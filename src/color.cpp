#include "color.hpp"
#include "utils.hpp"


float Color::red() const { return _red; }

float Color::green() const { return _green; }
float Color::blue() const { return _blue; }


Color operator+(const Color &lhs, const Color &rhs) {
    return Color(lhs.red()+rhs.red(),
                 lhs.green() + rhs.green(),
                 lhs.blue() + rhs.blue());
}

Color operator-(const Color &lhs, const Color &rhs) {
    return Color(lhs.red() - rhs.red(),
                 lhs.green() - rhs.green(),
                 lhs.blue() - rhs.blue());
}

Color operator*(const Color &lhs, const float rhs) {
    return Color(lhs.red()*rhs, lhs.green() *rhs, lhs.blue()*rhs);
}

Color operator*(const Color &lhs, const Color &rhs) {
    return Color(lhs.red() * rhs.red(),
                 lhs.green() * rhs.green(),
                 lhs.blue() * rhs.blue());
}

bool operator==(const Color &lhs, const Color &rhs) {
    return almost_eq(lhs.red(), rhs.red(), 0.0001f) 
        && almost_eq(lhs.green(), rhs.green(), 0.0001f)
        && almost_eq(lhs.blue(), rhs.blue(), 0.0001f);
}
