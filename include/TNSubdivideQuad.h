#ifndef TNSUBDIVIDEQUAD_H
#define TNSUBDIVIDEQUAD_H

#include <TNQuad.h>

#include "TNVector.h"

class TNSubdivideQuad : public TNQuad
{
    public:
        TNSubdivideQuad(TNPoint p1, TNPoint p2, TNPoint p3, TNPoint p4);
        virtual ~TNSubdivideQuad();
        virtual void render();
        void subdivideBy(int divisions);
    protected:
        int divisions;
        inline void fastRenderQuad(TNPoint p1,TNVector nl1, TNPoint p2, TNVector nl2, TNPoint p3, TNVector nl3, TNPoint p4,TNVector nl4);
    private:
};

#endif // TNSUBDIVIDEQUAD_H
