#ifndef TNTURRET_H
#define TNTURRET_H

#include "TNObject.h"
#include "TNCube.h"
#include "TNManager.h"

class TNTurret : public TNObject
{

    public:
        TNTurret(TNPoint loc, TNManager *mgr);
        virtual ~TNTurret();
        virtual void render();
    protected:
        TNCube base;
        TNCube top;
        TNCube barrel;
        float rot;
        TNManager *manager;
        double lastFire;
        TNMaterial blackPlastic;
        TNMaterial fire;
        int hasFired;
    private:
        void fireGun();
};

#endif // TNTURRET_H
