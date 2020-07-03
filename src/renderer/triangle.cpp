#include "renderer/triangle.hpp"
#include "renderer/vector/vec3d.hpp"


Triangle::Triangle(Vec3d p1, Vec3d p2, Vec3d p3) : p1(p1), p2(p2), p3(p3)
{
}

void Triangle::scale(double factor)
{
    p1 *= factor;
    p2 *= factor;
    p3 *= factor;
}


void Triangle::rotateX(double rad)
{
    p1.rotateX(rad);
    p2.rotateX(rad);
    p3.rotateX(rad);

    calcAvgZ();
}

void Triangle::rotateY(double rad)
{
    p1.rotateY(rad);
    p2.rotateY(rad);
    p3.rotateY(rad);

    calcAvgZ();
}

void Triangle::rotateZ(double rad)
{
    p1.rotateZ(rad);
    p2.rotateZ(rad);
    p3.rotateZ(rad);

    calcAvgZ();
}


void Triangle::translateX(double amount)
{
    p1.translateX(amount);
    p2.translateX(amount);
    p3.translateX(amount);
}

void Triangle::translateY(double amount)
{
    p1.translateY(amount);
    p2.translateY(amount);
    p3.translateY(amount);
}

void Triangle::translateZ(double amount)
{
    p1.translateZ(amount);
    p2.translateZ(amount);
    p3.translateZ(amount);

    calcAvgZ();
}

void Triangle::translate(Vec3d v)
{
    p1 += v;
    p2 += v;
    p3 += v;
}


void Triangle::calcAvgZ()
{
    avgZ = (p1.z() + p2.z() + p3.z()) / 3;
}