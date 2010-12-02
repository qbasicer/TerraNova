#ifndef TNOBJECT_H
#define TNOBJECT_H

#include "TNPoint.h"

class TNObject
{
    public:
        TNObject();
        virtual ~TNObject();
        virtual void render() = 0;
    protected:
        TNPoint location;
    private:
};

#endif // TNOBJECT_H
