#include "TNPhysicsObject.h"
#include <TNUtil.h>

#include <cmath>
#include <cstdlib>

TNPhysicsObject::TNPhysicsObject()
{
    mass = 0;
    friction = 0;
    useFriction = 0;
    useAccel = 0;
    useFriction = 0;
    last = 0;
}

TNPhysicsObject::~TNPhysicsObject()
{
    //dtor
}




void TNPhysicsObject::physicsFrame(){
    //Bail if we don't need to be here
    if(!active){return;}

    //If this is the first call, note the time so we can calculate elapsed next time around
    if(last == 0){
        last = meTime();
        return;
    }

    //Get elapsed time and update last update
    float newLast = meTime();
    float elapsed = newLast - last;
    last = newLast;

    //If the values are close enough to zero, shut-em-off
    if(useAccel && fabsf(getAcceleration().getLength()) < 0.001){
        setAcceleration(TNVector(0.0,0.0,0.0));
    }

    if(useVelocity && fabsf(getVelocity().getLength()) < 0.001){
        setVelocity(TNVector(0.0,0.0,0.0));
    }

    if(useAccel){
        velocity.Settx(velocity.Gettx() + (acceleration.Gettx() * elapsed));
        velocity.Setty(velocity.Getty() + (acceleration.Getty() * elapsed));
        velocity.Settz(velocity.Gettz() + (acceleration.Gettz() * elapsed));
    }

    if(useFriction && friction != 0.0){
        velocity.Settx(velocity.Gettx() * (1.0 - friction));
        velocity.Setty(velocity.Getty() * (1.0 - friction));
        velocity.Settz(velocity.Gettz() * (1.0 - friction));
    }

    if(useVelocity){
        loc.setX(loc.x() + (velocity.Gettx() * elapsed));
        loc.setY(loc.x() + (velocity.Getty() * elapsed));
        loc.setZ(loc.x() + (velocity.Gettz() * elapsed));
    }


}
