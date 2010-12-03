#include "TNPhysicsEngine.h"

#include <unistd.h>
#include "TNUtil.h"
#include <iostream>

using namespace std;

TNPhysicsEngine::TNPhysicsEngine()
{

    pthread_mutexattr_t attr;
    pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mut,&attr);

    this->start();
    //ctor
}

TNPhysicsEngine::~TNPhysicsEngine()
{
    //dtor
}


void TNPhysicsEngine::addObject(TNPhysicsObject *obj){
    objs.push_back(obj);
}

void TNPhysicsEngine::removeObject(TNPhysicsObject *obj){
    vector<TNPhysicsObject*>::iterator itr;
    for(itr = objs.begin(); itr != objs.end(); itr++){
        if(*itr == obj){
            objs.erase(itr);
            break;
        }
    }
    return;

}

void TNPhysicsEngine::run(){
    int t = time(0);
    int cycles = 0;
    int sleepTime = 10000;
    while ( !shutdownRequested() ){
        cycles++;
        vector<TNPhysicsObject*>::iterator itr;
        for(itr = objs.begin(); itr != objs.end(); itr++){
            TNPhysicsObject *obj = *itr;
            obj->physicsFrame();
        }

        for(itr = rq.begin(); itr != rq.end(); itr++){
            TNPhysicsObject *obj = *itr;
            removeObject(obj);
        }

        if(t != time(0)){
            sleepTime = calcSleeptime(1, sleepTime, cycles, 30, 40);
            cout << "Physics FPS:" << cycles << endl;
		    cycles = 0;
		    t = time(0);
		}
		usleep(sleepTime);
    }
}

void TNPhysicsEngine::queueForRemoval(TNPhysicsObject *obj){
    getLock();
    rq.push_back(obj);
    releaseLock();
}

void TNPhysicsEngine::getLock(){
    pthread_mutex_lock(&mut);
}

void TNPhysicsEngine::releaseLock(){
    pthread_mutex_unlock(&mut);
}

