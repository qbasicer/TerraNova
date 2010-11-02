#ifndef TNINPUTMANAGER_H
#define TNINPUTMANAGER_H

class TNInputManager;

#include <pthread.h>
#include "TNManager.h"

class TNInputManager
{
    public:
        TNInputManager(TNManager *imgr);
        virtual ~TNInputManager();

        void start();
    protected:
        virtual void run() = 0;

        TNManager *manager;
    private:
        static void* start_thread(void *obj);
        pthread_t thread;
};

#endif // TNINPUTMANAGER_H
