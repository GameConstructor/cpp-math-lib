#pragma once

#include "Vector3D.h"
#include "assert.h"


const Vector3D& Vector3D::Zero_Vector() 
{
    static Vector3D zero_vector;

    return zero_vector;
}

Vector3D::Vector3D()
{
    for ( int i = 0; i < dimension; i++ ) v[i] = 0.0f;
}

Vector3D::Vector3D( const Vector3D& other )
{
    *this = other;
}

Vector3D::Vector3D( Scalar element[3] )
{
    for ( int i = 0; i < dimension; i++ )
        v[i] = element[i];
}

Vector3D::Vector3D( double x, double y, double z )
{
    v[X] = (Scalar) x;
    v[Y] = (Scalar) y;
    v[Z] = (Scalar) z;
}

Scalar& Vector3D::operator []( int index )
{
    assert( index >= 0 && index < 3 );
    return v[index];
}

Scalar Vector3D::operator []( int index ) const
{
    return v[index];
}

Scalar Vector3D::Length() const
{
    Scalar length = 0.0;
    for ( int i = 0; i < dimension; i++ ) length += v[i] * v[i];
    length = Math::sqrt( length );
    return length;
}

void Vector3D::Normalize()
{
    Scalar length = Length();
    for ( int i = 0; i < dimension; i++ )
        v[i] /= length;
}

void Vector3D::operator *= ( Scalar scalar )
{
    for ( int i = 0; i < dimension; i++ )
        v[i] *=  scalar;
}

void Vector3D::operator *= ( const Vector3D& other )
{
    for ( int i = 0; i < dimension; i++ )
        v[i] *=  other.v[i];
}

Vector3D Vector3D::operator * ( Scalar scalar ) const
{
    Vector3D result;
    for ( int i = 0; i < dimension; i++ )
        result.v[i] =  v[i] * scalar;
    return result;
}

Vector3D operator * ( Scalar scalar, const Vector3D& vector )
{
    Vector3D result;
    for ( int i = 0; i < result.dimension; i++ )
        result.v[i] =  scalar * vector.v[i];
    return result;
}

void Vector3D::operator += ( const Vector3D& other )
{
    for ( int i = 0; i < dimension; i++ )
        v[i] += other.v[i];
}

void Vector3D::operator -= ( const Vector3D& other )
{
    for ( int i = 0; i < dimension; i++ )
        v[i] -= other.v[i];
}

Vector3D Vector3D::operator + ( const Vector3D& other ) const
{
    Vector3D result;
    for ( int i = 0; i < dimension; i++ )
        result.v[i] = v[i] + other.v[i];
    return result;
}

Vector3D Vector3D::operator - ( const Vector3D& other ) const
{
    Vector3D result;
    for ( int i = 0; i < dimension; i++ )
        result.v[i] = v[i] - other.v[i];
    return result;
}

Vector3D Vector3D::operator - ( void ) const
{
    Vector3D result;
    for ( int i = 0; i < dimension; i++ ) result.v[i] = -v[i];
    return result;
}

Scalar Vector3D::operator * ( const Vector3D& other ) const
{	// Dor Product
    Scalar dot_product = 0.0;
    for ( int i = 0; i < dimension; i++ )
        dot_product += v[i] * other.v[i];
    return dot_product;
}

Vector3D Vector3D::Cross_Product( const Vector3D& other )
{
    Vector3D result;

    result.v[X] = v[Y] * other.v[Z] - other.v[Y] * v[Z];
    result.v[Y] = v[Z] * other.v[X] - other.v[Z] * v[X];
    result.v[Z] = v[X] * other.v[Y] - other.v[X] * v[Y];

    return result;
}

bool Vector3D::operator == ( const Vector3D& other ) const
{
    bool result = true;

    for ( int i = 0; i < dimension; i++ )
        result &= v[i] == other.v[i];
    return result;
}

bool Vector3D::operator != ( const Vector3D& other ) const
{
    return ! (*this == other);
}
