#ifndef TNCUBE_H
#define TNCUBE_H

#include <TNObject.h>
#include "TNQuad.h"

class TNCube : public TNObject
{
    public:
        TNCube(){size = 0.0f;}
        TNCube(float size);
        virtual ~TNCube();
        virtual void render();
        void setSize(float size){this->size = size;build();}
    protected:
        float size;
        TNQuad *left;
        TNQuad *right;
        TNQuad *front;
        TNQuad *back;
    private:
        void build();
};

#endif // TNCUBE_H
