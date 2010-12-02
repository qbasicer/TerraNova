#include "TNPolygon.h"
#include <iostream>

using namespace std;

TNPolygon::TNPolygon(TNPoint p1, TNPoint p2, TNPoint p3)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;


    TNVector v1;
    TNVector v2;
    v1 = TNVector::subtract(p2,p1);
    v2 = TNVector::subtract(p3,p1);
    n1 = TNVector::crossProduct(v1,v2).norm();

    v1 = TNVector::subtract(p3,p2);
    v2 = TNVector::subtract(p1,p2);
    n2 = TNVector::crossProduct(v1,v2).norm();

    v1 = TNVector::subtract(p1,p3);
    v2 = TNVector::subtract(p2,p3);
    n3 = TNVector::crossProduct(v1,v2).norm();

    cout << "N1: " << n1.x() << "," << n1.y() << "," << n1.z() << endl;
    cout << "N2: " << n2.x() << "," << n2.y() << "," << n2.z() << endl;
    cout << "N3: " << n3.x() << "," << n3.y() << "," << n3.z() << endl;

    useMat = true;

    //Looking from front
    /*
          p1



      p2     p3
    */
}

TNPolygon::~TNPolygon()
{
    //dtor
}

void TNPolygon::render(){
    //glLoadIdentity( );
    //glTranslatef( -1.5f, 0.0f, -6.0f );
    //glColor3f(0.0,0.75,0.0);
    if(useMat){
        material.render();
    }
    glBegin(GL_TRIANGLES);
        glNormal3f(n1.x(),n1.y(),n1.z());
        glColor3f(   1.0f,  0.0f,  0.0f );
        glVertex3f(p1.x(), p1.y(), p1.z());

        glNormal3f(n2.x(),n2.y(),n2.z());
        glColor3f(   0.0f,  1.0f,  0.0f );
        glVertex3f(p2.x(), p2.y(), p2.z());

        glNormal3f(n3.x(),n3.y(),n3.z());
        glColor3f(   0.0f,  0.0f,  1.0f );
        glVertex3f(p3.x(), p3.y(), p3.z());
    glEnd();
    glFlush();
}

