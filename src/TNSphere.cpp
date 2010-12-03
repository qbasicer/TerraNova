#include "TNSphere.h"

#include <iostream>

using namespace std;

TNSphere::TNSphere(TNPoint loc, float radius)
{
    qobj = gluNewQuadric();
    this->radius = radius;
    location = loc;
    //ctor
}

TNSphere::~TNSphere()
{
    //dtor
}

void TNSphere::render(){
    glPushMatrix();
    material.render();
    glTranslated(location.x(),location.y(),location.z());
    gluSphere(qobj,radius,20,20);
    glPopMatrix();
}
