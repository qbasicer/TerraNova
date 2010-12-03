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
        virtual void render(){}
    protected:
        TNCamera *camera;
        float forwardSpeed;
        float rightSpeed;
        int isFlying;
        TNManager *manager;
    private:
};

#endif // TNPLAYER_H
