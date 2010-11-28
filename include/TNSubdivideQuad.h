#ifndef TNSUBDIVIDEQUAD_H
#define TNSUBDIVIDEQUAD_H

#include <TNQuad.h>


class TNSubdivideQuad : public TNQuad
{
    public:
        TNSubdivideQuad(TNPoint p1, TNPoint p2, TNPoint p3, TNPoint p4);
        virtual ~TNSubdivideQuad();
        virtual void render();
        void subdivideBy(int divisions);
    protected:
        int divisions;
        inline void fastRenderQuad(TNPoint p1,TNPoint p2, TNPoint p3, TNPoint p4);
    private:
};

#endif // TNSUBDIVIDEQUAD_H
