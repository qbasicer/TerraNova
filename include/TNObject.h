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

        /* May or may not be honoured by objects! */
        /* Ie quads and polys */
        virtual void setObjectLocation(TNPoint loc){this->location = loc;}
		virtual TNPoint getObjectLocation(){return location;}
		virtual void hurt(float amt){health -= amt;}
		virtual float getRadius(){return -1.0f;}
    protected:
        TNPoint location;
        TNMaterial material;
		float health;
    private:
};

#endif // TNOBJECT_H
