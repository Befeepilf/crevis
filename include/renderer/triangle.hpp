#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "renderer/vector/vec3d.hpp"

class Triangle
{
    public:
        explicit Triangle(Vec3d p1, Vec3d p2, Vec3d p3);
        Vec3d p1;
        Vec3d p2;
        Vec3d p3;

        double avgZ;
};

#endif // TRIANGLE_H