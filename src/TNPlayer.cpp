#include "TNPlayer.h"

#include "TNPlayerCamera.h"

#include "TNUtil.h"
#include <TNProjectile.h>

#include "math.h"

#include <iostream>

using namespace std;

TNPlayer::TNPlayer(TNManager *mgr)
{
    camera = new TNPlayerCamera(this);
    isFlying = 0;
    health = 100;
    manager = mgr;
}

TNPlayer::~TNPlayer()
{
    //dtor
}

void TNPlayer::setRightSpeed(float speed){
    cout << "Setting right speed to " << speed << endl;
    rightSpeed = speed;
    updateDirectionVelocity();
}

void TNPlayer::fireGun(){
    float yaw = camera->getYaw();
    float pitch = -camera->getPitch();
    float y = SIN_DEG(pitch);
    TNVector vec(SIN_DEG(yaw)*4,y*4,-COS_DEG(yaw)*4,0);

    TNProjectile *proj = new TNProjectile(TNPoint(-loc.x(),loc.y(),-loc.z()), vec,this,manager);
}

void TNPlayer::updateDirectionVelocity(){

    float yaw = camera->getYaw();
    float pitch = -camera->getPitch();
    float y = 0;
    if(isFlying){
        y = -SIN_DEG(pitch);
    }
    TNVector vec(-SIN_DEG(yaw),y,COS_DEG(yaw),0);
    TNVector up(0,1,0);
    TNVector side = TNVector::crossProduct(vec,up);

    vec.setLength(forwardSpeed);

    side.setLength(rightSpeed);

    TNVector result(vec.x() + side.x(), vec.y() + side.y(), vec.z() + side.z());
    setVelocity(result);
}
