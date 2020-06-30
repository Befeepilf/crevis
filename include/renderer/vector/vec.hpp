#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

class Vec
{
    public:
        Vec(std::vector<double> components);
        double length(void);

        std::vector<double> components;

        // operator overload: scale this vector
        void operator*=(const double s);
};

#endif // VECTOR_H