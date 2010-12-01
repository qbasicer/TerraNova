#ifndef TNMANAGER_H
#define TNMANAGER_H

class TNManager;

#include "TNInputManager.h"
#include "TNRenderEngine.h"
#include "TNTextureManager.h"
#include "TNPhysicsEngine.h"

class TNManager
{
    public:
        TNManager();
        virtual ~TNManager();

        TNInputManager *getInput(){return input;}
        void setInput(TNInputManager *in){input = in;}
        TNRenderEngine *getRenderEngine(){return re;}
        void setRenderEngine(TNRenderEngine *eng){re = eng;}
        TNTextureManager *getTextureManager(){return textures;}

        TNPhysicsEngine *getPhysicsEngine(){return physics;}



        void exec();
        void shutdown();
    protected:
        TNInputManager *input;
        TNRenderEngine *re;
        TNTextureManager *textures;
        TNPhysicsEngine *physics;
    private:

};

#endif // TNMANAGER_H
