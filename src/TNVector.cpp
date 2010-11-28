#include "TNVector.h"
#include <math.h>
#include <iostream>

using namespace std;

TNVector::TNVector()
{
    //ctor
}

TNVector::~TNVector()
{
    //dtor
}

void TNVector::setLength(float length){
    float unit = getLength();

    tx = (tx/unit)*length;
    ty = (ty/unit)*length;
    tz = (tz/unit)*length;

    if(getLength() != length){
        cerr << "Saddd Vector is sad" << endl;
    }
}

float TNVector::getLength(){
    return sqrtf(Gettx()*Gettx() + Getty() * Getty() + Gettz() * Gettz());
}
