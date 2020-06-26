#include "renderer/vector/vec3d.hpp"

#include <cmath>


Vec3d::Vec3d(double x, double y, double z) : Vec2d(x, y)
{
    components.push_back(z);
}

double Vec3d::z()
{
    return components[2];
}

void Vec3d::rotateZ(double angle)
{    
    double oldX = components[0];
    double oldY = components[1];

    components[0] = oldX * std::cos(angle) - oldY * std::sin(angle);
    components[1] = oldX * std::sin(angle) + oldY * std::cos(angle);
}