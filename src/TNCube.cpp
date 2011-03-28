#include "TNCube.h"

#include <GL/gl.h>
#include <GL/glu.h>

TNCube::TNCube(float size)
{
    this->size = size;
    build();
}

TNCube::TNCube(float h, float w, float d){
    h = h/2;
    w = w/2;
    d = d/2;
    TNPoint p1(w,h,d);
    TNPoint p2(w,-h,d);
    TNPoint p3(w,-h,-d);
    TNPoint p4(w ,h,-d);

    left = new TNQuad(p1,p2,p3,p4);

    p1 = TNPoint(-w,h,d);
    p2 = TNPoint(-w,-h,d);
    p3 = TNPoint(w,-h,d);
    p4 = TNPoint(w,h,d);

    back = new TNQuad(p1,p2,p3,p4);

    p1 = TNPoint(-w,h,d);
    p4 = TNPoint(-w,-h,d);
    p3 = TNPoint(-w,-h,-d);
    p2 = TNPoint(-w,h,-d);

    right = new TNQuad(p1,p2,p3,p4);

    p1 = TNPoint(-w,h,-d);
    p2 = TNPoint(w,h,-d);
    p3 = TNPoint(w,-h,-d);
    p4 = TNPoint(-w,-h,-d);

    front = new TNQuad(p1,p2,p3,p4);
}

TNCube::~TNCube()
{
    delete left;
    delete right;
    delete front;
    delete back;
}

#define COLOR() glColor3f(   0.75f,  0.75f,  0.75f );

void TNCube::render(){
    if(front == NULL || right == NULL || back == NULL || front == NULL){
        build();
    }else{
        front->render();
        back->render();
        left->render();
        right->render();
    }
}

void TNCube::setMaterial(TNMaterial mat){
    left->setMaterial(mat);
    right->setMaterial(mat);
    front->setMaterial(mat);
    back->setMaterial(mat);
}

void TNCube::build(){
    float hsize = size/2;
    TNPoint p1(hsize,hsize,hsize);
    TNPoint p2(hsize,-hsize,hsize);
    TNPoint p3(hsize,-hsize,-hsize);
    TNPoint p4(hsize ,hsize,-hsize);

    left = new TNQuad(p1,p2,p3,p4);


    p1 = TNPoint(-hsize,hsize,hsize);
    p2 = TNPoint(-hsize,-hsize,hsize);
    p3 = TNPoint(hsize,-hsize,hsize);
    p4 = TNPoint(hsize,hsize,hsize);

    back = new TNQuad(p1,p2,p3,p4);

    p1 = TNPoint(-hsize,hsize,hsize);
    p4 = TNPoint(-hsize,-hsize,hsize);
    p3 = TNPoint(-hsize,-hsize,-hsize);
    p2 = TNPoint(-hsize,hsize,-hsize);

    right = new TNQuad(p1,p2,p3,p4);

    p1 = TNPoint(-hsize,hsize,-hsize);
    p2 = TNPoint(hsize,hsize,-hsize);
    p3 = TNPoint(hsize,-hsize,-hsize);
    p4 = TNPoint(-hsize,-hsize,-hsize);

    front = new TNQuad(p1,p2,p3,p4);

}






