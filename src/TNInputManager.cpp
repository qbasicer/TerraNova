#include "TNInputManager.h"

TNInputManager::TNInputManager(TNManager *imgr)
{
    manager = imgr;
}

TNInputManager::~TNInputManager()
{
    //dtor
}


void TNInputManager::start(){
    pthread_create(&thread, 0, &TNInputManager::start_thread, this);
}

void* TNInputManager::start_thread(void *obj){
    reinterpret_cast<TNInputManager *>(obj)->run();
}
