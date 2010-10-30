#ifndef TNPOLYGON_H
#define TNPOLYGON_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <TNObject.h>
#include "TNPoint.h"


class TNPolygon : public TNObject
{
    public:
        TNPolygon(TNPoint p1, TNPoint p2, TNPoint p3);
        virtual ~TNPolygon();
        virtual void render();
    protected:
        TNPoint p1;
        TNPoint p2;
        TNPoint p3;
    private:
};

#endif // TNPOLYGON_H
