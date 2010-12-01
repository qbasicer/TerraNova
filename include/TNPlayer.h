#ifndef TNPLAYER_H
#define TNPLAYER_H

#include <TNPhysicsObject.h>
#include "TNCamera.h"

class TNPlayer : public TNPhysicsObject
{
    public:
        TNPlayer();
        virtual ~TNPlayer();
        virtual void cameraRender(){camera->render();}
        virtual TNCamera* getCamera(){return camera;};
        void setForwardSpeed(float speed){forwardSpeed = speed;}
        void updateDirectionVelocity();
    protected:
        TNCamera *camera;
        float forwardSpeed;
    private:
};

#endif // TNPLAYER_H
