#include "TNPhysicsEngine.h"

#include <unistd.h>
#include "TNUtil.h"
#include <iostream>

using namespace std;

TNPhysicsEngine::TNPhysicsEngine()
{
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
        if(t != time(0)){
            sleepTime = calcSleeptime(1, sleepTime, cycles, 30, 40);
            cout << "Physics FPS:" << cycles << endl;
		    cycles = 0;
		    t = time(0);
		}
		usleep(sleepTime);
    }
}

