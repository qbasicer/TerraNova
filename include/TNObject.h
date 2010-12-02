#ifndef TNOBJECT_H
#define TNOBJECT_H

class TNObject;

#include "TNPoint.h"
#include "TNMaterial.h"

class TNObject
{
    public:
        TNObject();
        virtual ~TNObject();
        virtual void render() = 0;
        virtual TNMaterial getMaterial(){return material;}
        virtual void setMaterial(TNMaterial mat){material = mat;}
    protected:
        TNPoint location;
        TNMaterial material;
    private:
};

#endif // TNOBJECT_H
