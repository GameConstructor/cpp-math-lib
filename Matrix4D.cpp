
#include <assert.h>
#include "Matrix4D.h"

Matrix4D::Matrix4D(void)
{
    for ( int row = 0; row < dimension; row++ )
        for ( int col = 0; col < dimension; col++ )
            m[row][col] = (Scalar)0.0;
}

Matrix4D::Matrix4D( Vector3D Bx, Vector3D By, Vector3D Bz )
{
    Identity();
    for ( int row = 0; row < dimension-1; row++ ) m[row][X] = Bx[row];
    for ( int row = 0; row < dimension-1; row++ ) m[row][Y] = By[row];
    for ( int row = 0; row < dimension-1; row++ ) m[row][Z] = Bz[row];
}

Matrix4D::Matrix4D( Vector4D Bx, Vector4D By, Vector4D Bz, Vector4D Bw )
{
    Identity();
    for ( int row = 0; row < dimension; row++ ) m[row][X] = Bx[row];
    for ( int row = 0; row < dimension; row++ ) m[row][Y] = By[row];
    for ( int row = 0; row < dimension; row++ ) m[row][Z] = Bz[row];
    for ( int row = 0; row < dimension; row++ ) m[row][W] = Bw[row];
}

void Matrix4D::Identity()
{
    for ( int row = 0; row < dimension; row++ )
        for ( int col = 0; col < dimension; col++ )
            m[row][col] = ( row == col ) ? (Scalar)1.0 : (Scalar)0.0;
}

void Matrix4D::Scaling( Vector3D scaling )
{
    Identity();
    for ( int i = 0; i < dimension-1; i++ )
        m[i][i] = scaling[i];
}

void Matrix4D::Scale( Scalar uniform_scale )
{
    Matrix4D scaling_matrix;
    scaling_matrix.Scaling( Vector3D( uniform_scale, uniform_scale, uniform_scale ) );
    *this *= scaling_matrix;
}

void Matrix4D::Scale( Vector3D scaling )
{
    Matrix4D scaling_matrix;
    scaling_matrix.Scaling( scaling );
    *this *= scaling_matrix;
}

inline double Degrees_to_Radians( double angle )
{
    return angle / 180.0 * Math::PI;
}

void Matrix4D::Rotation( double angle, int axis )
{
    double radians = Degrees_to_Radians( angle );
    Scalar cos = (Scalar) Math::cos( radians );
    Scalar sin = (Scalar) Math::sin( radians );

    Identity();  // really needed for 3D

    switch ( axis )
    {
        case X:
            m[Y][Y] =  cos;
            m[Y][Z] = -sin;
            m[Z][Y] =  sin;
            m[Z][Z] =  cos;
            break;

        case Y:
            m[Z][Z] =  cos;
            m[Z][X] = -sin;
            m[X][Z] =  sin;
            m[X][X] =  cos;
            break;

        case Z:
            m[X][X] =  cos;
            m[X][Y] = -sin;
            m[Y][X] =  sin;
            m[Y][Y] =  cos;
            break;
        default:
            assert( false );
            break;
    }
}

void Matrix4D::Rotate( double angle, int axis )
{
    Matrix4D rotation_matrix;
    rotation_matrix.Rotation( angle, axis );
    *this *= rotation_matrix;
}

void Matrix4D::Shearing( Vector2D shearing, int axis )
{
    Identity();
    switch ( axis )
    {
        case Z:
            m[X][Z] = shearing[0];
            m[Y][Z] = shearing[1];
            break;
        case Y:
            m[Z][Y] = shearing[0];
            m[X][Y] = shearing[1];
            break;
        case X:
            m[Y][X] = shearing[0];
            m[Z][X] = shearing[1];
            break;
        default:
            assert( false );
            break;
    }
}

void Matrix4D::Shear( Vector2D shear, int axis )
{
    Matrix4D shearing_matrix;
    shearing_matrix.Shearing( shear, axis );
    *this *= shearing_matrix;
}

void Matrix4D::Translation( Vector3D& translation )
{
    Identity();
    for ( int i = 0; i < dimension-1; i++ )
        m[i][W] = translation[i];
}

void Matrix4D::Translate( Vector3D& translation )
{
    Matrix4D translation_matrix;
    translation_matrix.Translation( translation );
    *this *= translation_matrix;
}

Matrix4D Matrix4D::operator + ( const Matrix4D& other ) const
{
    Matrix4D result;

    for ( int row = 0; row < dimension; row++ )
        for ( int col = 0; col < dimension; col++ )
            result.m[row][col] = m[row][col] + other.m[row][col];

    return result;
}

Matrix4D Matrix4D::operator - ( const Matrix4D& other ) const
{
    Matrix4D result;

    for ( int row = 0; row < dimension; row++ )
        for ( int col = 0; col < dimension; col++ )
            result.m[row][col] = m[row][col] - other.m[row][col];

    return result;
}

Matrix4D Matrix4D::operator * ( const Matrix4D& other ) const
{
    Matrix4D result;

    for ( int row = 0; row < dimension; row++ )
        for ( int col = 0; col < dimension; col++ )
            for ( int k = 0; k < dimension; k++ )
                result.m[row][col] += other.m[row][k] * m[k][col];

    return result;
}

void Matrix4D::operator *= ( const Matrix4D& other )
{
    Matrix4D tmp;

    for ( int row = 0; row < dimension; row++ )
        for ( int col = 0; col < dimension; col++ )
            for ( int k = 0; k < dimension; k++ )
                tmp.m[row][col] += other.m[row][k] * m[k][col];

    *this = tmp;
}

Vector4D Matrix4D::operator * ( const Vector4D& vector ) const
{
    Vector4D result;

    for ( int row = 0; row < dimension; row++ )
        for ( int col = 0; col < dimension; col++ )
            result[row] += m[row][col] * vector[col];

    return result;
}

void operator *= ( Vector4D& vector, const Matrix4D& matrix )
{
    Vector4D tmp;

    for ( int row = 0; row < matrix.dimension; row++ )
        for ( int col = 0; col < matrix.dimension; col++ )
            tmp[row] += matrix.m[row][col] * vector[col];

    vector = tmp;
}

Scalar Matrix4D::Determinant2D( int row, int col ) const
{
    Scalar result;

    int row1, row2, col1, col2;
    row1 = (row+1)%dimension;
    row2 = (row+2)%dimension;
    col1 = (col+1)%dimension;
    col2 = (col+2)%dimension;

    result = m[row1][col1] * m[row2][col2] - m[row1][col2] * m[row2][col1];

    return result;
}

Scalar Matrix4D::Determinant() const
{
    Scalar result = 0;

    for ( int col = 0; col < dimension; col++ )
        result += m[0][col] * Determinant2D( 0, col );

    return result;
}


Matrix4D Matrix4D::Inverse() 
{
    Matrix4D result;

    Scalar one_over_determinant = 1.0f / Determinant();

    for ( int row = 0; row < dimension; row++ )
        for ( int col = 0; col < dimension; col++ )
            result.m[col][row] = Determinant2D( row, col ) * one_over_determinant;

    return result;
}

inline void Matrix4D::Swap_Rows( int row1, int row2 )
{
    for ( int j = 0; j < dimension; j++ )
    {
        Scalar tmp;
        tmp = m[row1][j];
        m[row1][j] = m[row2][j];
        m[row2][j] = tmp;
    }
}

void Matrix4D::Invert()
{
    Matrix4D inverse;
    inverse.Identity();

    if ( Math::fabs( m[0][0] ) < Math::fabs( m[1][0] ) ) Swap_Rows( 0, 1 );

    Scalar one_over = 1.0f / m[0][0]; 
    Scalar scale_factor = m[1][0];

    // generate row echelon form
    for ( int j = 0; j < dimension; j++ )
    {
        m[0][j]			*= one_over;
        inverse.m[0][j] *= one_over;
        m[1][j]			-= m[0][j] * scale_factor;
        inverse.m[1][j] -= inverse.m[0][j] * scale_factor;
    }
    // back substitution
    one_over = 1.0f / m[1][1];
    scale_factor = m[0][1];
    for ( int j = dimension-1; j >= 0; j-- )
    {
        m[1][j]			*= one_over;
        inverse.m[1][j] *= one_over;
        m[0][j]			-= m[1][j] * scale_factor;
        inverse.m[0][j]	-= inverse.m[1][j] * scale_factor;
    }
    *this = inverse;
}

bool Matrix4D::operator == ( const Matrix4D& other ) const
{
    bool result = true;

    for ( int i = 0; i < dimension; i++ )
        for ( int j = 0; j < dimension; j++ )
            result &= m[i][j] == other.m[i][j];
    return result;
}

bool Matrix4D::operator != ( const Matrix4D& other ) const
{
    return ! (*this == other);
}

const Matrix4D& Matrix4D::Identity_Matrix()
{
    static Matrix4D identity_matrix;
    static bool identity_initialize = false;

    if ( !identity_initialize ) { identity_matrix.Identity(); identity_initialize = true; }

    return identity_matrix;
}

