#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

class Vec
{
    public:
        Vec(std::vector<double> components);
        double length(void);

        std::vector<double> components;
};

#endif // VECTOR_H