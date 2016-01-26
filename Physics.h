#pragma once

#include "Vector2D.h"
#include "Matrix3D.h"

class Physics
{
public:
    Vector2D position;
    Vector2D velocity;
    Physics();
    ~Physics();

    //Setter Functions
    void Set_Position( Vector2D );
    void Set_Velocity( Vector2D );
    void Set_Acceleration( Vector2D );
    void Add_Force( Vector2D );
    void Calculate_Momentum();
    void Calculate_Weight();
    void Calculate_NormalForce( double );
    void Set_Impulse( Vector2D );
    void Set_Mass( Scalar );
    void Set_Friction( Scalar );

    void Add_Torque( Vector2D );

    //Getter Function
    inline Vector2D Gravity()        const { return gravity; }
    inline Scalar Speed()            const { return velocity.Length(); }
    inline Vector2D Position()        const { return position; }
    inline Vector2D Velocity()        const { return velocity; }
    inline Vector2D Acceleration()    const { return acceleration; }
    inline Vector2D Momentum()        const { return momentum; }
    inline Vector2D NormalForce()    const { return normalForce; }
    inline Vector2D Impulse()        const { return impulse; }
    inline Scalar Mass()            const { return mass; }

    //Integrator
    Vector2D dX( double dt );


private:
    Vector2D acceleration;
    Vector2D gravity;
    Vector2D momentum;
    Vector2D impulse;
    Scalar mass;
    Scalar COF;    // coefficient of resitution
    Scalar frictionMagnitude;

    //Forces
    Vector2D netForce;
    Vector2D weight;
    Vector2D normalForce;
    Vector2D friction;

    //Rotation variables
    Vector2D netTorque;
    Vector2D angularVelocity;
    Vector2D angularAcceleration;
    Vector2D angularMomentum;
    Matrix3D inverseInertiaTensor;
};
