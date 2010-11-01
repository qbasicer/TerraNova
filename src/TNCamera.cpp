#include <GL/gl.h>
#include <GL/glu.h>
#include "TNCamera.h"
#include <iostream>
using namespace std;

TNCamera::TNCamera()
{
    //ctor
}

TNCamera::TNCamera(float x, float y, float z){
    loc.set(x,y,z);
}

TNCamera::~TNCamera()
{
    //dtor
}

void TNCamera::lookAt(float x, float y, float z){
    cerr << "[!!!] TNCamera::lookAt not implemented" << endl;
}

void TNCamera::render(){
    glRotatef( pitch, 1.0f, 0.0f , 0.0f );
    glRotatef( yaw, 0.0, 1.0f , 0.0f );
    glTranslatef(loc.x(), loc.y(), loc.z());
}
