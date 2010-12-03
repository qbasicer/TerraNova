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

        virtual void queueForRemoval(TNPhysicsObject *obj);

        void getLock();
        void releaseLock();
    protected:
        virtual void run();
    private:
        std::vector<TNPhysicsObject*> objs;
        std::vector<TNPhysicsObject*> rq;
        pthread_mutex_t mut;
        pthread_mutex_t mq;
        pthread_t owner;
};

#endif // TNPHYSICSENGINE_H
