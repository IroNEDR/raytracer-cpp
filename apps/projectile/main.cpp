#include "tuple.hpp"
#include "canvas.hpp"
#include <fstream>

struct Projectile {
    Tuple position;    
    Tuple velocity;
};

struct Environment {
    Tuple gravity;
    Tuple wind;
};

Projectile tick(Environment env,Projectile proj) {
    auto pos { proj.position + proj.velocity };
    auto vel { proj.velocity + env.gravity + env.wind };
    return Projectile(pos, vel);
}


int main() {
    auto p { Projectile(
        Tuple::Point(0.0f, 1.0f, 0.0f),
        Tuple::Vector(1.0f, 1.8f, 0.0f).normalize() * 11.25
    )};

    auto e {Environment(
        Tuple::Vector(0.0f, -0.1f, 0.0f),
        Tuple::Vector(-0.01f, 0.0f, 0.0f)
    )};
    auto c {Canvas(1200, 800)};

    auto x = static_cast<int>(p.position.x());
    auto y = static_cast<int>(p.position.y());
    while(y > 0) {
        p = tick(e,p);
        x = static_cast<int>(p.position.x());
        y = static_cast<int>(p.position.y());
        if ( x < c.width() && y < c.height() && x >= 0 && y >= 0) {
            c.write_pixel(x, c.height() - y, Color(1.0f, 0.0f, 0.0f));
        }
    }

    auto ppm { c.to_ppm() };
    std::ofstream outfile("projectile.ppm");
    outfile << ppm;

    return 0;

}
