#ifndef TNHEALTHPOWERUP_H
#define TNHEALTHPOWERUP_H

#include <TNObject.h>
#include <TNManager.h>
#include <TNCube.h>
#include <time.h>

class TNHealthPowerup : public TNObject
{
    public:
        TNHealthPowerup(TNPoint origin, TNManager *mgr);
        virtual ~TNHealthPowerup();
    protected:
        virtual void render();
        TNCube *cube;
        float rot;
        int active;
        time_t t;
        TNManager *mgr;
    private:

};

#endif // TNHEALTHPOWERUP_H
