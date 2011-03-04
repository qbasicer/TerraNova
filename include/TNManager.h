#ifndef TNMANAGER_H
#define TNMANAGER_H

class TNManager;

#include "TNInputManager.h"
#include "TNRenderEngine.h"
#include "TNTextureManager.h"
#include "TNPhysicsEngine.h"
#include "TNThread.h"
#include <vector>
#include <semaphore.h>

class TNManager : public TNThread
{
    public:
        TNManager();
        virtual ~TNManager();

        TNInputManager *getInput(){return input;}
        void setInput(TNInputManager *in){input = in;}
        TNRenderEngine *getRenderEngine(){return re;}
        void setRenderEngine(TNRenderEngine *eng);
        TNTextureManager *getTextureManager(){return textures;}

        TNPhysicsEngine *getPhysicsEngine(){return physics;}
		void newEnemy(){numEnemies++;}
		void destroyEnemy();
        void delayedDeletion(TNObject *obj);

        void exec();
        void shutdown();
    protected:
        std::vector<TNObject*> deferredDelete;
        TNInputManager *input;
        TNRenderEngine *re;
        TNTextureManager *textures;
        TNPhysicsEngine *physics;
        int numEnemies;
        virtual void run();
        sem_t sem;
    private:

};

#endif // TNMANAGER_H
