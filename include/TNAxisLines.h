#ifndef TNAXISLINES_H
#define TNAXISLINES_H

#include "TNPoint.h"
#include "TNObject.h"

class TNAxisLines : public TNObject
{
    public:
        TNAxisLines(TNPoint loc);
        virtual ~TNAxisLines();
        virtual void render();
    protected:
        TNPoint loc;
    private:
};

#endif // TNAXISLINES_H
