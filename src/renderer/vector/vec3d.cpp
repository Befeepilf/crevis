#include "renderer/vector/vec3d.hpp"


Vec3d::Vec3d(double x, double y, double z) : Vec({x, y, z})
{
}

double Vec3d::x()
{
    return components[0];
}

double Vec3d::y()
{
    return components[1];
}

double Vec3d::z()
{
    return components[2];
}