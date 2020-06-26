#ifndef THREE_D_VECTOR_H
#define THREE_D_VECTOR_H

#include "renderer/vector/vec2d.hpp"

class Vec3d : public Vec2d
{
    public:
        Vec3d(double x, double y, double z);
        double z(void);
        void rotateZ(double angle);
};

#endif // THREE_D_VECTOR_H