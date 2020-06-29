#include "renderer/vector/vec2d.hpp"

#include <cmath>


Vec2d::Vec2d(const double x, const double y) : Vec({x, y})
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

void Vec2d::rotateX(const double angle)
{
    const double oldY = components[1];
    const double oldZ = components[2];

    components[1] = oldY * std::cos(angle) - oldZ * std::sin(angle);
    components[2] = oldY * std::sin(angle) + oldZ * std::cos(angle);
}

void Vec2d::rotateY(const double angle)
{
    const double oldX = components[0];
    const double oldZ = components[2];

    components[0] = oldX * std::cos(angle) + oldZ * std::sin(angle);
    components[2] = -oldX * std::sin(angle) + oldZ * std::cos(angle);
}


// operator overload: add two vectors
Vec2d Vec2d::operator+(Vec2d v)
{
    return Vec2d(x() + v.x(), y() + v.y());
}

// operator overload: substract two vectors
Vec2d Vec2d::operator-(Vec2d v)
{
    return Vec2d(x() - v.x(), y() - v.y());
}

// operator overload: scale copy of this vector
Vec2d Vec2d::operator*(const double s)
{
    return Vec2d(x() * s, y() * s);
}

// operator overload: scale copy of this vector
Vec2d Vec2d::operator/(const double s)
{
    return Vec2d(x() / s, y() / s);
}