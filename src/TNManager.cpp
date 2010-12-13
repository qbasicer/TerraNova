#include "TNManager.h"

#include <iostream>
using namespace std;
#include <TNTurret.h>

/* TNManager is essentially the central management for the entire application */

TNManager::TNManager()
{
    textures = new TNTextureManager();
    physics = new TNPhysicsEngine();
	numEnemies = 0;
	srand(time(0));


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
	sleep(2);
    int num = rand() % 4 + 1;
	cout << "Adding " << num << endl;
	for(int i = 0; i < num; i++){
		float x = (rand() % 40) - 20;
		float z = (rand() % 40) - 20;
		TNPoint loc(x,-1,z);
		TNTurret *tur = new TNTurret(loc,this);
		re->addObject(tur);
	}
    physics->wait();
    re->wait();
    input->wait();
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

void TNManager::shutdown(){
	physics->stop();
    input->stop();
    re->stop();
}

