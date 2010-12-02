#include "TNTurret.h"

#include <GL/gl.h>
#include <GL/glu.h>

#define BASE_SIZE   0.75
#define TOP_SIZE    0.50
#define BARREL_SIZE    0.1
#define BARREL_LENGTH   1.5

TNTurret::TNTurret(TNPoint loc)
{
    location = loc;
    base.setSize(BASE_SIZE);
    top.setSize(TOP_SIZE);
    barrel.setSize(BARREL_SIZE);
    rot = 0;
    //ctor
}

TNTurret::~TNTurret()
{
    //dtor
}

void TNTurret::render(){
    rot++;
    glPushMatrix();
    glTranslatef(location.x(), location.y()+(BASE_SIZE/2.0), location.z());
    base.render();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(location.x(), location.y()+(BASE_SIZE)+(TOP_SIZE/2), location.z());
    glRotatef(rot,0,1,0);
    top.render();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(location.x(), location.y()+(BASE_SIZE)+(TOP_SIZE/2), location.z());
    glRotatef(rot,0,1,0);
    glScaled(1.0,1.0,(BARREL_LENGTH)/BARREL_SIZE);
    glTranslated(0,0,BARREL_SIZE/2);
    barrel.render();
    glPopMatrix();
}
