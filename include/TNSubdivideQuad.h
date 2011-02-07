#ifndef TNSUBDIVIDEQUAD_H
#define TNSUBDIVIDEQUAD_H

#include <TNQuad.h>

#include "TNVector.h"
#include <pthread.h>

class TNSubdivideQuad : public TNQuad
{
    public:
        TNSubdivideQuad(TNPoint p1, TNPoint p2, TNPoint p3, TNPoint p4);
        virtual ~TNSubdivideQuad();
        virtual void render();
        void subdivideBy(int divisions);
        void renderingMode(int mode);
    protected:
        int divisions;
        inline void renderStoredQuad(int p1, int p2, int p3, int p4);
        inline void fastRenderQuad(TNPoint p1,TNVector nl1, TNPoint p2, TNVector nl2, TNPoint p3, TNVector nl3, TNPoint p4,TNVector nl4);
        inline void fastRenderQuadPtr(TNPoint *p1,TNVector *nl1, TNPoint *p2, TNVector *nl2, TNPoint *p3, TNVector *nl3, TNPoint *p4,TNVector *nl4);
    private:
        TNPoint **pts;
        TNVector **norms;
        pthread_mutex_t mut;
};

#endif // TNSUBDIVIDEQUAD_H
