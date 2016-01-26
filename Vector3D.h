#pragma once

#include "Scalar.h"

class Vector3D
{
public:
    Vector3D();
    Vector3D( const Vector3D& );    // copy constructor
    Vector3D( Scalar element[3] ); // initialize with an array
    Vector3D( double x, double y, double z );

    Scalar& operator [] ( int index );            // use to both read and write elements, just like a normal array
    Scalar  operator [] ( int index ) const;    //  use to read elements from a const vector

    Scalar Length() const;
    void   Normalize();

    void     operator *= ( Scalar );
    Vector3D operator *  ( Scalar ) const;
    friend Vector3D operator * ( Scalar, const Vector3D& );

    Vector3D operator -  ( void ) const;    // negative sign
    void     operator += ( const Vector3D& );
    void     operator -= ( const Vector3D& );
    Vector3D operator +  ( const Vector3D& ) const;
    Vector3D operator -  ( const Vector3D& ) const;
    void     operator *= ( const Vector3D& ); // component multiplication
    Scalar   operator *  ( const Vector3D& ) const;    // the DOT PRODUCT

    Vector3D Cross_Product( const Vector3D& );

    bool     operator == ( const Vector3D& ) const;
    bool     operator != ( const Vector3D& ) const;

    // use this to test whethere or not a vector == zero vector
    static const Vector3D& Zero_Vector();

protected:
    static const int dimension = 3;
    Scalar v[dimension];
};
