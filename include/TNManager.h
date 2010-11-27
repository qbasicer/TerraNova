#ifndef TNMANAGER_H
#define TNMANAGER_H

class TNManager;

#include "TNInputManager.h"
#include "TNRenderEngine.h"
#include "TNTextureManager.h"

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
        void exec();
        void shutdown();
    protected:
        TNInputManager *input;
        TNRenderEngine *re;
        TNTextureManager *textures;
    private:

};

#endif // TNMANAGER_H
