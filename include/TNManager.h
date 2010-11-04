#ifndef TNMANAGER_H
#define TNMANAGER_H

class TNManager;

#include "TNInputManager.h"
#include "TNRenderEngine.h"

class TNManager
{
    public:
        TNManager();
        virtual ~TNManager();

        TNInputManager *getInput(){return input;}
        void setInput(TNInputManager *in){input = in;}
        TNRenderEngine *getRenderEngine(){return re;}
        void setRenderEngine(TNRenderEngine *eng){re = eng;}
        void exec();
        void shutdown();
    protected:
        TNInputManager *input;
        TNRenderEngine *re;
    private:

};

#endif // TNMANAGER_H
