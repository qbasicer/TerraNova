#ifndef TNTHREAD_H
#define TNTHREAD_H

#include <pthread.h>

class TNThread
{
    public:
        TNThread();
        virtual ~TNThread();
        void start();
    protected:
        virtual void run() = 0;
    private:
        static void* start_thread(void *obj);
        pthread_t thread;
};

#endif // TNTHREAD_H
