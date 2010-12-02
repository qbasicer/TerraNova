#ifndef TNPOLYGON_H
#define TNPOLYGON_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <TNObject.h>
#include "TNPoint.h"
#include "TNVector.h"


class TNPolygon : public TNObject
{
    public:
        TNPolygon(TNPoint p1, TNPoint p2, TNPoint p3);
        virtual ~TNPolygon();
        virtual void render();
        void useMaterial(int enabled){useMat = enabled;}
    protected:
        TNPoint p1;
        TNPoint p2;
        TNPoint p3;

        TNVector n1;
        TNVector n2;
        TNVector n3;

        int useMat;
    private:
};

#endif // TNPOLYGON_H
