#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "renderer/vector/vector3d.hpp"

class Triangle
{
    public:
        explicit Triangle(Vector3d p1, Vector3d p2, Vector3d p3);
        Vector3d p1;
        Vector3d p2;
        Vector3d p3;
};

#endif // TRIANGLE_H