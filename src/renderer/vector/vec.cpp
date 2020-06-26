#include "renderer/vector/vec.hpp"

#include <cmath>
#include <iostream>
#include <vector>

Vec::Vec(std::vector<double> components) : components(components)
{
    // create initial transformation matrix which is the identity matrix of size n x n where n is the number of dimensions of this vector
    // std::vector<std::vector<double>> transformMatrix (components.size(), std::vector<double> (components.size(), 0));
    // for (unsigned int i = 0; i < components.size(); i++)
    // {
    //     transformMatrix[i][i] = 1;
    // }
}

double Vec::length()
{
    double sum = 0;
    for (double c : components)
    {
        sum += pow(c, 2);
    }

    return sqrt(sum);
}

// operator overload: add two vectors
Vec Vec::operator+(Vec v)
{
    Vec new_v (components);

    for (unsigned int i = 0; i < v.components.size(); i++)
    {
        new_v.components[i] += v.components[i];
    }

    return new_v;
}

// operator overload: scale copy of this vector
Vec Vec::operator*(double s)
{
    Vec new_v (components);

    for (unsigned int i = 0; i < new_v.components.size(); i++)
    {
        new_v.components[i] *= s;
    }

    return new_v;
}

// operator overload: scale this vector
Vec Vec::operator*=(double s)
{
    for (unsigned int i = 0; i < components.size(); i++)
    {
        components[i] *= s;
    }

    return *this;
}

// operator overload: dot product
double Vec::operator*(Vec v)
{
    double sum = 0;

    for (unsigned int i = 0; i < components.size(); i++)
    {
        sum += components[i] * v.components[i];
    }

    return sum;
}