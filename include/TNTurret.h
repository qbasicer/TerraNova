#ifndef TNTURRET_H
#define TNTURRET_H

#include "TNObject.h"
#include "TNCube.h"

class TNTurret : public TNObject
{

    public:
        TNTurret(TNPoint loc);
        virtual ~TNTurret();
        virtual void render();
    protected:
        TNCube base;
        TNCube top;
        TNCube barrel;
        float rot;
    private:
};

#endif // TNTURRET_H
