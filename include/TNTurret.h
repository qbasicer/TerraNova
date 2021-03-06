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
		virtual float getRadius(){return 1.0f;}
		virtual void hurt(float amt);
    protected:
        TNCube base;
        TNCube top;
        TNCube barrel;
        float rot;
        TNManager *manager;
        double lastFire;
        TNMaterial blackPlastic;
        TNMaterial fire;
        TNMaterial silver;
        TNMaterial gold;
        int hasFired;
        double ctime;
    private:
        void fireGun();
};

#endif // TNTURRET_H
