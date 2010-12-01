#ifndef TNPHYSICSENGINE_H
#define TNPHYSICSENGINE_H

#include <vector>

class TNPhysicsEngine;

#include "TNPhysicsObject.h"
#include "TNThread.h"

class TNPhysicsEngine  : public TNThread
{
    public:
        TNPhysicsEngine();
        virtual ~TNPhysicsEngine();
        virtual void addObject(TNPhysicsObject *obj);
        virtual void removeObject(TNPhysicsObject *obj);

    protected:
        virtual void run();
    private:
        std::vector<TNPhysicsObject*> objs;
};

#endif // TNPHYSICSENGINE_H
