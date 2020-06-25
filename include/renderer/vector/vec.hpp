#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

class Vec
{
    public:
        Vec(std::vector<double> components);
        double length(void);

        std::vector<double> components;

        // operator overload: add two vectors
        Vec operator+(const Vec v);

        // operator overload: scale copy of this vector
        Vec operator*(const double s);
        // operator overload: scale this vector
        Vec operator*=(const double s);

        // operator overload: dot product
        double operator*(const Vec v);
};

#endif // VECTOR_H