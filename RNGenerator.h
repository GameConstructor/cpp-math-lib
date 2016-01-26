#pragma once

#include <cmath>

#ifndef NULL
#define NULL 0
#endif

#define RNG_MAX 2147483647

#define EXPORT_API __declspec(dllexport)

class EXPORT_API RNGenerator
{
public:

    ~RNGenerator( void )
    {
        if(instance)
            delete instance;
    }

    static RNGenerator* Instance( void ) 
    {
        if(!instance)
            instance = new RNGenerator();

        return instance; 
    }
    
    static inline void SetSeed( unsigned int newSeed ) { seed = newSeed; }
    static inline unsigned int GetSeed( void )         { return seed; }

    //Generates a number (0...1) using LCG method MINSTD : X_(i) = 16807 * X_(i-1) mod(2^31 - 1)
    //need a temp cast to a 64 bit number for the seed to avoid overflow problems
    //if the number overflows in the arithmetic, the period is greatly reduced.
    static inline float fGenerate( void ) 
    { 
        seed = ( unsigned long long )seed * ( unsigned int )16807 % ( unsigned int )RNG_MAX;
        return ( float )seed / ( float )RNG_MAX ; 
    }

    static inline double dGenerate(void) 
    { 
        seed = ( unsigned long long )seed * ( unsigned int )16807 % ( unsigned int )RNG_MAX;
        return ( double )seed / ( double )RNG_MAX ; 
    }

    //Probability distribution variates
    static float Uniform( float a, float b );
    static double Uniform( double a, double b );

    static float Exponential( float B );
    static double Exponential( double B );

    static float Weibull( float a, float b, float c );
    static double Weibull( double a, double b, double c);

    static float Triangle( float Xmin, float Xmax, float c);
    static double Triangle ( double Xmin, double Xmax, double c);

    static float Normal( float Mean );
    static double Normal (double Mean );


private:
    //Make constructors / assignment private for singleton operation
    RNGenerator() { seed = 1; }
    RNGenerator(RNGenerator&) {}
    RNGenerator& operator= (RNGenerator&) { return *this; }

    static unsigned int seed;
    static RNGenerator* instance;
};