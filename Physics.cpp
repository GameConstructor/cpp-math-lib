#include "Physics.h"

const float gravitational_accleration = -980.0f;

Physics::Physics()
{
    gravity = Vector2D( 0.0f, gravitational_accleration );
}

Physics::~Physics()
{
}

void Physics::Set_Position( Vector2D position )
{
    this->position = position;
}

void Physics::Set_Velocity( Vector2D velocity )
{
    this->velocity = velocity;
}

void Physics::Set_Acceleration( Vector2D acceleration )
{
    this->acceleration = acceleration;
}

void Physics::Add_Force( Vector2D force )
{
    netForce += force;
}

void Physics::Calculate_Momentum()
{
    momentum = mass * velocity;
}

void Physics::Calculate_Weight()
{
    weight = mass * gravity;
}

inline double Degrees_to_Radians( double angle )
{
    return angle / 180.0 * Math::PI;
}

void Physics::Calculate_NormalForce( double theta )
{
    double radians = Degrees_to_Radians( theta );
    normalForce[X] = weight.Length() * ( Scalar ) Math::sin( radians );
    normalForce[Y] = weight.Length() * ( Scalar ) Math::cos( radians );
}

void Physics::Set_Impulse( Vector2D impulse )
{
    this->impulse = impulse;
}

void Physics::Set_Mass( Scalar mass )
{
    this->mass = mass;
}

void Physics::Set_Friction( Scalar COF )
{
    this->COF = COF;
    frictionMagnitude = COF * ( -gravity * mass ).Length();
}

void Physics::Add_Torque( Vector2D torque )
{
    netTorque += torque;
}

Vector2D Physics::dX( double dt )
{
    Vector2D dX;
    Scalar delta_t = (Scalar) dt;
    Vector2D initial_velocity = velocity;

    Vector2D frictionDirection( velocity );
    frictionDirection.Normalize();
    friction = frictionDirection * -frictionMagnitude;

    netForce = normalForce + weight + friction;
    acceleration = netForce * ( 1 / mass );
    Vector2D final_velocity = acceleration * delta_t + initial_velocity;
    Vector2D average_velocity = (final_velocity + initial_velocity ) * 0.5f;
    dX = average_velocity * delta_t;
    velocity = final_velocity;
    position += dX;
    return dX;
}