#ifndef TNCAMERA_H
#define TNCAMERA_H

#include <TNObject.h>
#include <TNVector.h>
#include <TNPoint.h>


class TNCamera : public TNObject
{
    public:
        TNCamera();
        TNCamera(float x, float y, float z);
        virtual ~TNCamera();
        virtual void setLocation(TNPoint point){loc = point;}
        virtual TNPoint getLocation(){return loc;}
        float getPitch(){return pitch;}
        void setPitch(float angle){pitch = angle;}
        float getYaw(){return yaw;}
        void setYaw(float angle){yaw = angle;}
        void lookAt(float x, float y, float z);
        virtual void render();
    protected:
        TNPoint loc;
        float pitch;
        float yaw;
    private:
};

#endif // TNCAMERA_H
