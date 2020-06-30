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