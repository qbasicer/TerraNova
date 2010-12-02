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


void TNPlayer::updateDirectionVelocity(){
    if(forwardSpeed < 0.01 && forwardSpeed > -0.01){
        setVelocity(TNVector(0.0,0.0,0.0));
    }else{
        float yaw = camera->getYaw();
        float pitch = -camera->getPitch();
        float y = 0;
        if(isFlying){
            y = -SIN_DEG(pitch);
        }
        TNVector vec(-SIN_DEG(yaw),y,COS_DEG(yaw),0);
        setVelocity(vec);
    }
}
