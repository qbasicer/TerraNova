#include "TNManager.h"

#include <iostream>
using namespace std;

/* TNManager is essentially the central management for the entire application */

TNManager::TNManager()
{
    textures = new TNTextureManager();
    physics = new TNPhysicsEngine();
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
    re->wait();
    input->wait();
}

void TNManager::shutdown(){
    input->stop();
    re->stop();
}

