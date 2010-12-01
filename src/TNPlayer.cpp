#include "TNPlayer.h"

#include "TNPlayerCamera.h"

#include "TNUtil.h"

#include "math.h"

#include <iostream>

using namespace std;

TNPlayer::TNPlayer()
{
    camera = new TNPlayerCamera(this);
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

        TNVector vec(-SIN_DEG(yaw),-SIN_DEG(pitch),COS_DEG(yaw),0);
        cout << "Vec: " << vec.Gettx() << "," << vec.Getty() << "," << vec.Gettz() << endl;
        setVelocity(vec);
    }
}
