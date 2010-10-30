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
