#ifndef THREE_D_VECTOR_H
#define THREE_D_VECTOR_H

#include "renderer/vector/vec.hpp"

class Vec3d : public Vec
{
    public:
        Vec3d(double x, double y, double z);
        double x(void);
        double y(void);
        double z(void);
};

#endif // THREE_D_VECTOR_H