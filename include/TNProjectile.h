#ifndef TNPROJECTILE_H
#define TNPROJECTILE_H

#include <TNObject.h>
#include <TNPhysicsObject.h>
#include <TNManager.h>
#include <TNSphere.h>

class TNProjectile : public TNObject, public TNPhysicsObject
{
    public:
        TNProjectile(TNPoint origin, TNVector vec, TNObject *immune, TNManager *mgr);
        virtual ~TNProjectile();
        virtual void physicsFrame();
        virtual void render(){ball->render();}
    protected:
        TNPoint origin;
        TNVector vector;
        TNManager *manager;
        TNSphere *ball;
        TNMaterial fire;
        TNObject *immune;
    private:
};

#endif // TNPROJECTILE_H
