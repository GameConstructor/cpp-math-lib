#pragma once
#include "Vector2D.h"

class Ray2D;
struct RayIntersectLine;

class Line
{
private:
    Vector2D point;
    Vector2D normal;

public:
    Line();
    Line( Vector2D point, Vector2D normal );

    Scalar Distance( Vector2D point );

    friend RayIntersectLine Ray_Intersect_Line( Ray2D ray, Line line );
};

class Ray2D
{
public:
    Vector2D origin;
    Vector2D direction;
    Scalar   tmin, tmax;

    void Init();

public:
    Ray2D();
    Ray2D( Vector2D origin, Vector2D direction );

    friend RayIntersectLine Ray_Intersect_Line( Ray2D ray, Line line );
};

struct RayIntersectLine
{
    Scalar t;
    Vector2D point;
    Vector2D normal;
    enum { Intersect, Parallel, Coincident } type;

    RayIntersectLine()
    {
        t = Scalar( 0 );
    }
};

