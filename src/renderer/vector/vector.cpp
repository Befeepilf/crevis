#include "renderer/vector/vector.hpp"

#include <cmath>
#include <vector>

Vector::Vector(std::vector<double> components) : components(components)
{

}

double Vector::length()
{
    double sum = 0;
    for (double c : components)
    {
        sum += pow(c, 2);
    }

    return sqrt(sum);
}

// operator overload: add two vectors
Vector Vector::operator+(Vector v)
{
    Vector new_v (components);

    for (unsigned int i = 0; i < v.components.size(); i++)
    {
        new_v.components[i] += v.components[i];
    }

    return new_v;
}

// operator overload: scale this vector
Vector Vector::operator*(double s)
{
    Vector new_v (components);

    for (unsigned int i = 0; i < new_v.components.size(); i++)
    {
        new_v.components[i] *= s;
    }

    return new_v;
}

// operator overload: dot product
double Vector::operator*(Vector v)
{
    double sum = 0;

    for (unsigned int i = 0; i < components.size(); i++)
    {
        sum += components[i] * v.components[i];
    }

    return sum;
}