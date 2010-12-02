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
    ret.setx(a.y() * b.z() - a.z() * b.y());
    ret.sety(a.z() * b.x() - a.x() * b.z());
    ret.setz(a.x() * b.y() - a.y() * b.x());

    return ret;
}

TNVector TNVector::norm(){
    TNVector ret = *this;
    ret.setLength(1.0);
    return ret;
}
