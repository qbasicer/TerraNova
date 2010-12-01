#include "TNPlayerCamera.h"

#include <iostream>

using namespace std;

TNPlayerCamera::TNPlayerCamera(TNPlayer *player):TNCamera()
{
    this->player = player;
}

TNPlayerCamera::~TNPlayerCamera()
{
    //dtor
}

void TNPlayerCamera::render(){
    loc = getLocation();
    TNCamera::render();
}

void TNPlayerCamera::setLocation(TNPoint point){
    player->setLocation(point);
}

TNPoint TNPlayerCamera::getLocation(){
    return player->getLocation();
}
