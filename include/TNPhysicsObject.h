#ifndef TNPHYSICSOBJECT_H
#define TNPHYSICSOBJECT_H

#include <TNVector.h>
#include <TNPoint.h>

class TNPhysicsObject;

#include "TNPhysicsEngine.h"

class TNPhysicsObject
{
    public:
        TNPhysicsObject();
        virtual ~TNPhysicsObject();

        virtual void registerWithEngine(TNPhysicsEngine *eng);

        virtual TNPoint getLocation(){return loc;}
        virtual void setLocation(TNPoint loc){this->loc = loc;}

        virtual int isActive(){return active;}
        virtual void setActive(int state){active = state; last = 0;}

        virtual void setAcceleration(int enabled){useAccel = enabled;}
        virtual void setVelocity(int enabled){useVelocity = enabled;}
        virtual void setFriction(int enabled){useFriction = enabled;}

        virtual float getMass(){return mass;}
        virtual void setMass(float mass){this->mass = mass;}

        virtual float getFriction(){return friction;}
        virtual void setFriction(){this->friction = friction;}

        virtual TNVector getVelocity(){return velocity;}
        virtual void setVelocity(TNVector velo){this->velocity = velo;}

        virtual TNVector getAcceleration(){return acceleration;}
        virtual void setAcceleration(TNVector accel){this->acceleration = accel;}
        virtual void physicsFrame();
    protected:
        float mass;
        float friction;
        int useAccel;
        int useVelocity;
        int useFriction;
        TNVector acceleration;
        TNVector velocity;
        TNPoint loc;
        int active;
        double last;



    private:
        //We need this so we can clean ourselves up
        TNPhysicsEngine *engine;
};

#endif // TNPHYSICSOBJECT_H
