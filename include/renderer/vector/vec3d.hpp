#ifndef THREE_D_VECTOR_H
#define THREE_D_VECTOR_H

#include "renderer/vector/vec2d.hpp"

class Vec3d : public Vec2d
{
    public:
        Vec3d(const double x, const double y, const double z);
        double z(void);
        void rotateZ(const double angle);
        void translateZ(const double amount);

        // operator overload: add two vectors
        Vec3d operator+(Vec3d v);
        // operator overload: substract two vectors
        Vec3d operator-(Vec3d v);
        // operator overload: scale copy of this vector
        Vec3d operator*(const double s);
        // operator overload: dot product
        double operator*(Vec3d v);
        // operator overload: scale copy of this vector
        Vec3d operator/(const double s);
};

Vec3d crossProd(Vec3d v1, Vec3d v2);

#endif // THREE_D_VECTOR_H