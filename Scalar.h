#pragma once
#include <stdlib.h>

namespace Math
{
    #include <math.h>
    const double PI = 3.14159265358979323846;
}

typedef float Scalar;
const Scalar epsilon = Scalar( 1.0e-6 ); 
inline bool Within_Epsilon( double value )
{
    return value < epsilon && value > -epsilon;
}


const int X = 0;
const int Y = 1;
const int Z = 2;
const int W = 3;
