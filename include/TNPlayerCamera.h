#ifndef TNPLAYERCAMERA_H
#define TNPLAYERCAMERA_H

class TNPlayerCamera;

#include <TNCamera.h>
#include "TNPlayer.h"


class TNPlayerCamera : public TNCamera
{
    public:
        TNPlayerCamera(TNPlayer *player);
        virtual ~TNPlayerCamera();
        virtual void setLocation(TNPoint point);
        virtual TNPoint getLocation();
        virtual void render();
    protected:
        TNPlayer *player;
    private:
};

#endif // TNPLAYERCAMERA_H
