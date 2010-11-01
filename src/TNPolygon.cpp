#include "TNPolygon.h"
#include <iostream>

using namespace std;

TNPolygon::TNPolygon(TNPoint p1, TNPoint p2, TNPoint p3)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

TNPolygon::~TNPolygon()
{
    //dtor
}

void TNPolygon::render(){
    //glLoadIdentity( );
    //glTranslatef( -1.5f, 0.0f, -6.0f );
    //glColor3f(0.0,0.75,0.0);
    glBegin(GL_TRIANGLES);
        glColor3f(   1.0f,  0.0f,  0.0f );
        glVertex3f(p1.x(), p1.y(), p1.z());
        glColor3f(   0.0f,  1.0f,  0.0f );
        glVertex3f(p2.x(), p2.y(), p2.z());
        glColor3f(   0.0f,  0.0f,  1.0f );
        glVertex3f(p3.x(), p3.y(), p3.z());
    glEnd();
    glFlush();
}

