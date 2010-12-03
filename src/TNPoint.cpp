#include "TNPoint.h"

TNPoint::TNPoint(float x, float y, float z)
{
    this->tx = x;
    this->ty = y;
    this->tz = z;
	bSet = 1;
}

TNPoint::TNPoint(){
    this->tx = 0;
    this->ty = 0;
    this->tz = 0;
	bSet = 0;
}

void TNPoint::set(float x, float y, float z){
    tx = x;
    ty = y;
    tz = z;
	bSet = 1;
}
