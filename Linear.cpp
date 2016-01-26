#include "Linear.h"

void Ray2D::Init()
{
    tmin = 0.0;
    tmax = Scalar( Math::_HUGE );
}

Ray2D::Ray2D()
{
    Init();
}

Ray2D::Ray2D( Vector2D origin, Vector2D direction )
{
    Init();
    this->origin = origin;
    this->direction = direction;
}

/****      Line     ****/

Line::Line( Vector2D point, Vector2D normal )
{
    this->point = point;
    this->normal = normal;
    this->normal.Normalize();
}

Scalar Line::Distance( Vector2D point )
{
    return normal * ( point - this->point );
}


/****      Intersection     ****/


RayIntersectLine Ray_Intersect_Line( Ray2D ray, Line line )
{
    RayIntersectLine result;
    double numerator, denominator;

    numerator = line.normal * line.point - line.normal * ray.origin;
    denominator = line.normal * ray.direction;

    if ( Within_Epsilon( denominator ) )
    {
        if ( Within_Epsilon( numerator ) )
        {
            result.type = RayIntersectLine::Coincident;
            result.t = 0.0;
        }
        else
        {
            result.type = RayIntersectLine::Parallel;
            result.t = Scalar( Math::_HUGE );
        }
    }
    else
    {
        result.t = Scalar( numerator / denominator );
        result.normal = line.normal;
        result.type = RayIntersectLine::Intersect;
    }

    return result;
}

