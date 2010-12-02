#ifndef TNQUAD_H
#define TNQUAD_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <TNObject.h>
#include "TNPoint.h"
#include "TNVector.h"

class TNQuad : public TNObject
{
    public:
        TNQuad(TNPoint p1, TNPoint p2, TNPoint p3, TNPoint p4);
        virtual ~TNQuad();
        virtual void render();
        void setTexture(GLuint tex){textureId = tex;}
    protected:
        GLuint textureId;
        TNPoint p1;
        TNPoint p2;
        TNPoint p3;
        TNPoint p4;

        TNVector n1;
        TNVector n2;
        TNVector n3;
        TNVector n4;
    private:

};

#endif // TNQUAD_H
