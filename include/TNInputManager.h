#ifndef TNINPUTMANAGER_H
#define TNINPUTMANAGER_H

class TNInputManager;

#include <pthread.h>
#include "TNManager.h"
#include "TNThread.h"

class TNInputManager : public TNThread
{
    public:
        TNInputManager(TNManager *imgr);
        virtual ~TNInputManager();
    protected:
        TNManager *manager;

};

#endif // TNINPUTMANAGER_H
