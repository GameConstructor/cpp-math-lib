
#include "RNGenerator.h"

//static definition
unsigned int RNGenerator::seed  = 1;
RNGenerator* RNGenerator::instance = NULL;

float RNGenerator::Uniform( float a, float b )
{
    return fGenerate() * ( b - a ) + a;
}

double RNGenerator::Uniform( double a, double b )
{
    return dGenerate() * ( b - a ) + a;
}

/*NOTE*  Even though 1 - fGenerate() is equivalent to simply fGenerate() when considering the random numbers generated,
            if you use just fGenerate() then the values returned are backwards (inverted y) when trying to reproduce the graph of F(x).
*/
float RNGenerator::Exponential( float B )
{
    return -log( 1.0f - fGenerate() ) * B;
}

double RNGenerator::Exponential( double B )
{
    return -log( 1.0f - dGenerate() ) * B;
}

float RNGenerator::Weibull( float a, float b, float c)
{
    return a + ( pow( -log( 1.0f - fGenerate() ), 1/c ) * b  );
}

double RNGenerator::Weibull( double a, double b, double c)
{
    return a + ( pow( -log( 1.0f - dGenerate() ), 1/c ) * b );
}

float RNGenerator::Triangle( float Xmin, float Xmax, float c)
{
    float U = fGenerate();

    if ( U <= ( ( c - Xmin ) / ( Xmax - Xmin ) ) )
        return sqrt( U * ( c- Xmin) * ( Xmax - Xmin ) ) + Xmin;
    else
        return -sqrt( ( 1.0f - U ) * ( Xmax - Xmin ) * ( Xmax - c ) ) + Xmax;
}

double RNGenerator::Triangle( double Xmin, double Xmax, double c)
{
    double U = fGenerate();

    if ( U <= ( ( c - Xmin ) / ( Xmax - Xmin ) ) )
        return sqrt( U * ( c- Xmin) * ( Xmax - Xmin ) ) + Xmin;
    else
        return -sqrt( ( 1.0f - U ) * ( Xmax - Xmin ) * ( Xmax - c ) ) + Xmax;
}

float RNGenerator::Normal( float mean )
{
    float Y; 
    float U;

    do
    {
        Y = Exponential( 1.0f );
        U = fGenerate();
    }while ( U > exp( - pow( Y-1, 2 ) / 2.0f ) );

    if ( fGenerate() <= 0.5 )
        Y *= -1.0f;

    return Y + mean;
}

double RNGenerator::Normal( double mean )
{
    double Y; 
    double U; 

    do
    {
        Y = Exponential(1.0);
        U = dGenerate();
    }while ( U > exp( - pow( Y-1, 2.0) / 2.0 ) );

    if ( dGenerate() <= 0.5 )
        Y *= -1.0;

    return Y + mean;
}


/********************************************************************
*  Bridge C functions for C# Implementation
********************************************************************/

extern "C" EXPORT_API RNGenerator* CreateRNGenerator()
{
    return RNGenerator::Instance();
}

extern "C" EXPORT_API void DeleteRNGenerator( RNGenerator* pRNG )
{
    if(pRNG)
    {
        delete pRNG;
        pRNG = NULL;
    }
}

extern "C" EXPORT_API  void SetSeed( RNGenerator* pRNG, unsigned int nSeed )
{
    pRNG->SetSeed( nSeed );
}
extern "C" EXPORT_API  unsigned int GetSeed( RNGenerator* pRNG )
{
    return pRNG->GetSeed();
}

extern "C" EXPORT_API  float fGenerate( RNGenerator* pRNG )
{
    return pRNG->fGenerate();
}
extern "C" EXPORT_API  double dGenerate( RNGenerator* pRNG )
{
    return pRNG->dGenerate();
}

extern "C" EXPORT_API float fUniform( RNGenerator* pRNG, float a, float b )
{
    return pRNG->Uniform( a, b );
}
extern "C" EXPORT_API double dUniform( RNGenerator* pRNG, double a, double b )
{
    return pRNG->Uniform( a, b );
}

extern "C" EXPORT_API float fExponential( RNGenerator* pRNG, float B )
{
    return pRNG->Exponential( B );
}
extern "C" EXPORT_API double dExponential( RNGenerator* pRNG, double B )
{
    return pRNG->Exponential( B );
}

extern "C" EXPORT_API float fWeibull( RNGenerator* pRNG, float a, float b, float c )
{
    return pRNG->Weibull(a, b, c);
}
extern "C" EXPORT_API double dWeibull( RNGenerator* pRNG, double a, double b, double c )
{
    return pRNG->Weibull(a, b, c);
}

extern "C" EXPORT_API float fTriangle( RNGenerator* pRNG, float Xmin, float Xmax, float c )
{
    return pRNG->Triangle(Xmin, Xmax, c);
}
extern "C" EXPORT_API double dTriangle( RNGenerator* pRNG, double Xmin, double Xmax, double c )
{
    return pRNG->Triangle(Xmin, Xmax, c);
}

extern "C" EXPORT_API float fNormal( RNGenerator* pRNG, float mean )
{
    return pRNG->Normal( mean );
}
extern "C" EXPORT_API double dNormal( RNGenerator* pRNG, double mean )
{
    return pRNG->Normal( mean );
}