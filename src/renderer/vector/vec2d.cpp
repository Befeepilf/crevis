#include "renderer/vector/vec2d.hpp"


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