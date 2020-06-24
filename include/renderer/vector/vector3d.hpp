#ifndef THREE_D_VECTOR_H
#define THREE_D_VECTOR_H

#include "renderer/vector/vector.hpp"

class Vector3d : public Vector
{
    public:
        Vector3d(double x, double y, double z);
};

#endif // THREE_D_VECTOR_H