#ifndef TNPLAYER_H
#define TNPLAYER_H

class TNPlayer;

#include <TNPhysicsObject.h>
#include "TNCamera.h"
#include <TNManager.h>

class TNPlayer : public TNPhysicsObject, public TNObject
{
    public:
        TNPlayer(TNManager *mgr);
        virtual ~TNPlayer();
        virtual void cameraRender(){camera->render();}
        virtual TNCamera* getCamera(){return camera;};
        void setForwardSpeed(float speed){forwardSpeed = speed;}
        void setRightSpeed(float speed);
        void updateDirectionVelocity();
        float health;
        float getHealth(){return health;}
        void hurt(float amt){health -= amt;}
        void fireGun();
		double lastShot;
        virtual void render(){}
        virtual void setAimingBias(double x, double y){xab = x; yab = y;}
    protected:
        TNCamera *camera;
        float forwardSpeed;
        float rightSpeed;
        int isFlying;
        TNManager *manager;
        double xab;
        double yab;
    private:
};

#endif // TNPLAYER_H
