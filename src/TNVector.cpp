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

TNVector TNVector::subtract(TNPoint a, TNPoint b){
    TNVector ret;
    ret.Settx(a.x() - b.x());
    ret.Setty(a.y() - b.y());
    ret.Settz(a.z() - b.z());
    return ret;
}

TNVector TNVector::crossProduct(TNVector a, TNVector b){
    TNVector ret;
    // TODO: Implement!
    return ret;
}
