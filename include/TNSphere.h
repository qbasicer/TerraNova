#ifndef TNSPHERE_H
#define TNSPHERE_H

#include "TNObject.h"
#include <GL/glu.h>

class TNSphere : public TNObject
{
    public:
        TNSphere(TNPoint loc = TNPoint(), float radius = 1);
        virtual ~TNSphere();
        virtual void render();
    protected:
        GLUquadricObj *qobj;
        float radius;
    private:
};

#endif // TNSPHERE_H
