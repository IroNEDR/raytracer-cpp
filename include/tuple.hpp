#pragma once

class Tuple {
private:
    float _x,_y,_z,_w;
public:
    Tuple(const float x, const float y, const float z, const float w):_x(x),_y(y),_z(z),_w(w){}

    static Tuple Point(const float x, const float y, const float z);
    static Tuple Vector(const float x, const float y, const float z);
    bool isPoint() const;
    bool isVector() const;
    
    float x() const { return _x; }
    float y() const { return _y; }
    float z() const { return _z; }
    float w() const { return _w; }

    float magnitude() const;
    
};


bool operator==(const Tuple lhs, const Tuple rhs);
Tuple operator+(const Tuple lhs, const Tuple rhs);
Tuple operator-(const Tuple lhs, const Tuple rhs);
Tuple operator-(const Tuple t);
Tuple operator*(const Tuple lhs, float s);
Tuple operator/(const Tuple lsh, float d);
