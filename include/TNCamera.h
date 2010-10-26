#ifndef TNCAMERA_H
#define TNCAMERA_H

#include <TNObject.h>
#include <TNVector.h>


class TNCamera : public TNObject
{
    public:
        TNCamera();
        virtual ~TNCamera();
    protected:
        TNPoint loc;
        float pitch;
        float yaw;
    private:
};

#endif // TNCAMERA_H
