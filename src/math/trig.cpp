#include "math/trig.hpp"


const double PI = 3.14159265358979323846;

double radToDeg(double rad)
{
    return 180 / PI * rad;
}

double degToRad(double deg)
{
    return PI / 180 * deg;
}