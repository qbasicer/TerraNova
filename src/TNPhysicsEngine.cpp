#include "TNPhysicsEngine.h"

#include <unistd.h>
#include "TNUtil.h"
#include <iostream>
#include <cstdio>

using namespace std;

TNPhysicsEngine::TNPhysicsEngine()
{

    pthread_mutexattr_t attr;
    pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mut,&attr);
    pthread_mutex_init(&mq,&attr);
    owner = NULL;
    this->start();
    //ctor
}

TNPhysicsEngine::~TNPhysicsEngine()
{
    //dtor
}


void TNPhysicsEngine::addObject(TNPhysicsObject *obj){
    getLock();
    objs.push_back(obj);
    releaseLock();
}

void TNPhysicsEngine::removeObject(TNPhysicsObject *obj){
    getLock();
    vector<TNPhysicsObject*>::iterator itr;
    for(itr = objs.begin(); itr != objs.end(); itr++){
        if(*itr == obj){
            objs.erase(itr);
            break;
        }
    }
    releaseLock();
    return;

}

void TNPhysicsEngine::run(){
    int t = time(0);
    int cycles = 0;
    int sleepTime = 10000;
    while ( !shutdownRequested() ){
        cycles++;

        getLock();
        vector<TNPhysicsObject*>::iterator itr;
        for(itr = objs.begin(); itr != objs.end(); itr++){
            TNPhysicsObject *obj = *itr;
            obj->physicsFrame();
        }
        releaseLock();

        pthread_mutex_lock(&mq);
        for(itr = rq.begin(); itr != rq.end(); itr++){
            TNPhysicsObject *obj = *itr;
            removeObject(obj);
        }
        rq.clear();

        for(itr = aq.begin(); itr != aq.end(); itr++){
            TNPhysicsObject *obj = *itr;
            addObject(obj);
        }
        aq.clear();
        pthread_mutex_unlock(&mq);

        if(t != time(0)){
            sleepTime = calcSleeptime(1, sleepTime, cycles, 30, 40);
            cout << "Physics FPS:" << cycles << endl;
		    cycles = 0;
		    t = time(0);
		}
		usleep(sleepTime);
    }
}

void TNPhysicsEngine::removeObject(TNObject *obj){
    getLock();
    vector<TNPhysicsObject*>::iterator itr;
    for(itr = objs.begin(); itr != objs.end(); itr++){
        TNPhysicsObject *pobj = *itr;

        TNPhysicsObject* cobj = dynamic_cast<TNPhysicsObject*>(obj);

        if(cobj){
            printf("Removed physics object %p\n",cobj);
            removeObject(cobj);
            releaseLock();
            return;
        }
    }
    printf("No physics object %p here\n",obj);
    releaseLock();
}

void TNPhysicsEngine::queueForRemoval(TNPhysicsObject *obj){
    pthread_mutex_lock(&mq);
    rq.push_back(obj);
    pthread_mutex_unlock(&mq);
}

void TNPhysicsEngine::queueForAddition(TNPhysicsObject *obj){
    pthread_mutex_lock(&mq);
    printf("Adding physics object %p\n",obj);
    aq.push_back(obj);
    pthread_mutex_unlock(&mq);
}

void TNPhysicsEngine::getLock(){
    if(pthread_mutex_trylock(&mut)){
        if(owner != pthread_self()){
            pthread_mutex_lock(&mut);
        }
    }

    owner = pthread_self();
}

void TNPhysicsEngine::releaseLock(){
    pthread_mutex_unlock(&mut);
}

