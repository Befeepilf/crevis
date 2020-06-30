#ifndef TWO_D_VECTOR_H
#define TWO_D_VECTOR_H

#include "renderer/vector/vec.hpp"

class Vec2d : public Vec
{
    public:
        Vec2d(const double x, const double y);
        double x(void);
        double y(void);
        void rotateX(const double angle);
        void rotateY(const double angle);
        void translateX(const double amount);
        void translateY(const double amount);

        // operator overload: add two vectors
        Vec2d operator+(Vec2d v);
        // operator overload: substract two vectors
        Vec2d operator-(Vec2d v);
        // operator overload: scale copy of this vector
        Vec2d operator*(const double s);
        // operator overload: scale copy of this vector
        Vec2d operator/(const double s);
};


double perpDot(Vec2d v1, Vec2d v2);

#endif // TWO_D_VECTOR_H