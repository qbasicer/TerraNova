#include "TNThread.h"

TNThread::TNThread()
{
     shutDownRequested = 0;
}

TNThread::~TNThread()
{
    //dtor
}

void TNThread::start(){
    pthread_create(&thread, 0, &TNThread::start_thread, this);
}

void* TNThread::start_thread(void *obj){
    reinterpret_cast<TNThread *>(obj)->run();
    return NULL;
}

void TNThread::wait(){
    void *ret;
    pthread_join(thread, &ret);
}
