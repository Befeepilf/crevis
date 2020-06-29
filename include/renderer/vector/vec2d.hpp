#ifndef TWO_D_VECTOR_H
#define TWO_D_VECTOR_H

#include "renderer/vector/vec.hpp"

class Vec2d : public Vec
{
    public:
        Vec2d(const double x, const double y);
        double x(void);
        double y(void);
        void rotateY(const double angle);
        void rotateX(const double angle);

        // operator overload: add two vectors
        Vec2d operator+(Vec2d v);
        // operator overload: substract two vectors
        Vec2d operator-(Vec2d v);
        // operator overload: scale copy of this vector
        Vec2d operator*(const double s);
        // operator overload: scale copy of this vector
        Vec2d operator/(const double s);
};

#endif // TWO_D_VECTOR_H