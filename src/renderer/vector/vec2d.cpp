#include "renderer/vector/vec2d.hpp"

#include <cmath>


Vec2d::Vec2d(double x, double y) : Vec({x, y})
{
}

double Vec2d::x()
{
    return components[0];
}

double Vec2d::y()
{
    return components[1];
}

void Vec2d::rotateX(double angle)
{
    double oldY = components[1];
    double oldZ = components[2];

    components[1] = oldY * std::cos(angle) - oldZ * std::sin(angle);
    components[2] = oldY * std::sin(angle) + oldZ * std::cos(angle);
}

void Vec2d::rotateY(double angle)
{
    double oldX = components[0];
    double oldZ = components[2];

    components[0] = oldX * std::cos(angle) + oldZ * std::sin(angle);
    components[2] = -oldX * std::sin(angle) + oldZ * std::cos(angle);
}