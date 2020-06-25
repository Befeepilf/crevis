#ifndef TWO_D_VECTOR_H
#define TWO_D_VECTOR_H

#include "renderer/vector/vec.hpp"

class Vec2d : public Vec
{
    public:
        Vec2d(double x, double y);
        double x(void);
        double y(void);
};

#endif // TWO_D_VECTOR_H