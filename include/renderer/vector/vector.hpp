#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

class Vector
{
    public:
        Vector(std::vector<double> components);
        double length(void);

        std::vector<double> components;

        // operator overload: add two vectors
        Vector operator+(const Vector v);

        // operator overload: scale this vector
        Vector operator*(const double s);
        // operator overload: dot product
        double operator*(const Vector v);
};

#endif // VECTOR_H