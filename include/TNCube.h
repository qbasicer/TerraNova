#ifndef TNCUBE_H
#define TNCUBE_H

#include <TNObject.h>


class TNCube : public TNObject
{
    public:
        TNCube(){size = 0.0f;}
        TNCube(float size);
        virtual ~TNCube();
        virtual void render();
        void setSize(float size){this->size = size;}
    protected:
        float size;
    private:
};

#endif // TNCUBE_H
