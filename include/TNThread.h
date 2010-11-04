#ifndef TNTHREAD_H
#define TNTHREAD_H

#include <pthread.h>

class TNThread
{
    public:
        TNThread();
        virtual ~TNThread();
        void start();
        void stop(){shutDownRequested = 1;}
        void wait();
    protected:
        virtual void run() = 0;
        inline int shutdownRequested(){return shutDownRequested;}

    private:
        static void* start_thread(void *obj);
        pthread_t thread;
        int shutDownRequested;
};

#endif // TNTHREAD_H
