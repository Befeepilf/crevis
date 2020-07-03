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
        void calcAvgZ(void);

        void scale(double factor);

        void rotateX(double rad);
        void rotateY(double rad);
        void rotateZ(double rad);

        void translateX(double amount);
        void translateY(double amount);
        void translateZ(double amount);
        void translate(Vec3d v);
};

#endif // TRIANGLE_H