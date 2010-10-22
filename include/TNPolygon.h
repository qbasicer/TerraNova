#ifndef TNPOLYGON_H
#define TNPOLYGON_H

#include <TNObject.h>


class TNPolygon : public TNObject
{
    public:
        TNPolygon(float x, float y, float z);
        virtual ~TNPolygon();
        virtual void render();
    protected:
        float x;
        float y;
        float z;
    private:
};

#endif // TNPOLYGON_H
