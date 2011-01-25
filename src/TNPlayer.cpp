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
	lastShot = 0;
	forwardSpeed = 0;
	rightSpeed = 0;
}

TNPlayer::~TNPlayer()
{
    //dtor
}

void TNPlayer::setRightSpeed(float speed){
    rightSpeed = speed;
    updateDirectionVelocity();
}

void TNPlayer::fireGun(){
	if(meTime() - lastShot > 0.5){
	    float accuracy = manager->getRenderEngine()->getAccuracy();
	    float dev_x = (((float)(random() % 100)/100.0)-0.5) * accuracy * 5;
		float dev_y = (((float)(random() % 100)/100.0)-0.5) * accuracy * 5;
		float yaw = camera->getYaw() + dev_x;
		float pitch = -camera->getPitch() + dev_y;
		float y = SIN_DEG(pitch);

		cout << "dev_x " << dev_x << ", " << "dev_y " << dev_y << " accuracy " << accuracy << endl;
		cout << "yaw " << yaw << ", " << "pitch " << pitch << endl;


		TNVector vec(SIN_DEG(yaw)*8,y*8,-COS_DEG(yaw)*8,0);

		TNProjectile *proj = new TNProjectile(TNPoint(-loc.x(),loc.y(),-loc.z()), vec,this,manager);
		lastShot = meTime();
	}
}

void TNPlayer::updateDirectionVelocity(){
	if(loc.x() > 19){
		loc.setX(19);
	}else if(loc.x() < -19){
		loc.setX(-19);
	}

	if(loc.z() > 19){
		loc.setZ(19);
	}else if(loc.z() < -19){
		loc.setZ(-19);
	}
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
