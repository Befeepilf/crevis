#include "renderer/vector/vec3d.hpp"

#include <cmath>


Vec3d::Vec3d(const double x, const double y, const double z) : Vec2d(x, y)
{
    components.push_back(z);
}

double Vec3d::z()
{
    return components[2];
}

void Vec3d::rotateZ(const double angle)
{    
    const double oldX = components[0];
    const double oldY = components[1];

    components[0] = oldX * std::cos(angle) - oldY * std::sin(angle);
    components[1] = oldX * std::sin(angle) + oldY * std::cos(angle);
}


void Vec3d::translateZ(const double amount)
{
    components[2] += amount;
}


// operator overload: add two vectors
Vec3d Vec3d::operator+(Vec3d v)
{
    return Vec3d(x() + v.x(), y() + v.y(), z() + v.z());
}

// operator overload: substract two vectors
Vec3d Vec3d::operator-(Vec3d v)
{
    return Vec3d(x() - v.x(), y() - v.y(), z() - v.z());
}

// operator overload: scale copy of this vector
Vec3d Vec3d::operator*(const double s)
{
    return Vec3d(x() * s, y() * s, z() * s);
}

// operator overload: dot product
double Vec3d::operator*(Vec3d v)
{
    return x() * v.x() + y() * v.y() + z() * v.z();
}

// operator overload: scale copy of this vector
Vec3d Vec3d::operator/(const double s)
{
    return Vec3d(x() / s, y() / s, z() * s);
}


Vec3d crossProd(Vec3d v1, Vec3d v2)
{
    return Vec3d(
        v1.y() * v2.z() - v1.z() * v2.y(),
        v1.z() * v2.x() - v1.x() * v2.z(),
        v1.x() * v2.y() - v1.y() * v2.x()
    );
}