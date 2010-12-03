#include "TNPlayer.h"

#include "TNPlayerCamera.h"

#include "TNUtil.h"

#include "math.h"

#include <iostream>

using namespace std;

TNPlayer::TNPlayer()
{
    camera = new TNPlayerCamera(this);
    isFlying = 0;
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
    if(rightSpeed != 0){
        cout <<" Right speed! Yaw: " << yaw << " Yaw+90:" << (yaw+90) << result.x() <<  "," << result.y() << "," << result.z() << endl;
    }
    setVelocity(result);
}
