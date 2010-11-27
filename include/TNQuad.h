#ifndef TNQUAD_H
#define TNQUAD_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <TNObject.h>
#include "TNPoint.h"

class TNQuad : public TNObject
{
    public:
        TNQuad(TNPoint p1, TNPoint p2, TNPoint p3, TNPoint p4);
        virtual ~TNQuad();
        virtual void render();
        void setTexture(GLuint tex){textureId = tex;}
    protected:
    private:
        GLuint textureId;
        TNPoint p1;
        TNPoint p2;
        TNPoint p3;
        TNPoint p4;
};

#endif // TNQUAD_H
