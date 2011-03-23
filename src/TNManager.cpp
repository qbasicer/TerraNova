#include "TNManager.h"

#include <iostream>
using namespace std;
#include <TNTurret.h>
#include <TNUtil.h>

/* TNManager is essentially the central management for the entire application */

TNManager::TNManager()
{
    textures = new TNTextureManager();
    physics = new TNPhysicsEngine();
	numEnemies = 0;
	srand(time(0));
	sem_init(&sem, 0, 1);
}

void TNManager::setRenderEngine(TNRenderEngine *eng){
	re = eng;

}

TNManager::~TNManager()
{
    //dtor
}

void TNManager::exec(){
    cout << "TNManager starting threads" << endl;
    input->start();
    re->start();
    cout << "TNManager waiting for thread exit" << endl;
	usleep(2000000);
    int num = rand() % 4 + 1;
	cout << "Adding " << num << endl;
	for(int i = 0; i < num; i++){
		float x = (rand() % 40) - 20;
		float z = (rand() % 40) - 20;
		TNPoint loc(x,-1,z);
		TNTurret *tur = new TNTurret(loc,this);
		re->addObject(tur);
	}
	cout << "Starting manager thread" << endl;
	start();

	// Wait for the thread state to stabalize
    usleep(1000);
    physics->wait();
    cout << "Physics shut down" << endl;
    cout << "Waiting for render engine to shut down" << endl;
    re->wait();
    cout << "Waiting for input to shut down" << endl;
    input->wait();
    cout << "Waiting for manager to shut down" << endl;
    wait();

}

void TNManager::destroyEnemy(){
	numEnemies--;
	if(numEnemies == 0){
		int num = rand() % 4 + 1;
		for(int i = 0; i < num; i++){
			float x = (rand() % 40) - 20;
			float z = (rand() % 40) - 20;
			TNPoint loc(x,-1,z);
			TNTurret *tur = new TNTurret(loc,this);
			re->addObject(tur);
		}
	}
}

void TNManager::run(){
    while(!shutdownRequested()){
        sem_wait(&sem);
        for(unsigned int i = 0; i < deferredDelete.size(); i++){

            TNObject* obj = deferredDelete[i];
            re->removeObject(obj);
            physics->removeObject(obj);
            delete obj;
        }
        deferredDelete.clear();
        sem_post(&sem);
        usleep(100000);
    }
}

void TNManager::delayedDeletion(TNObject *obj){
    double start = meTime();
    int tries = 0;
    while(sem_trywait(&sem)){
        cout << "Waiting to get lock..." << endl;
        tries++;
        usleep(10000);
        if(tries > 100){
            cout << "**********************" << endl;
            cout << "**********************" << endl;
            cout << "* Danger Danger!     *" << endl;
            cout << "**********************" << endl;
            cout << "**********************" << endl;
            break;
        }
    }
    if(meTime() > (start+1.0)){
        cout << endl<<  "****" << endl << "Failed to add to deferred deletion list" << endl <<"****" << endl <<  endl;
        shutdown();
    }
    deferredDelete.push_back(obj);

    sem_post(&sem);
}


void TNManager::shutdown(){
    stop();
	physics->stop();
    input->stop();
    re->stop();
}

