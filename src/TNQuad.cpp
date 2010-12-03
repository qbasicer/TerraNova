#include "TNQuad.h"

#include <iostream>
using namespace std;

#define OPENGL_ERROR_CHECK()    if(err != GL_NO_ERROR)  cerr << "glError: " << gluErrorString(err) << endl;

TNQuad::TNQuad(TNPoint p1, TNPoint p2, TNPoint p3, TNPoint p4)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
    textureId = 0;

    TNVector v1;
    TNVector v2;
    v1 = TNVector::subtract(p2,p1);
    v2 = TNVector::subtract(p4,p1);
    n1 = TNVector::crossProduct(v1,v2).norm();

    v1 = TNVector::subtract(p3,p2);
    v2 = TNVector::subtract(p1,p2);
    n2 = TNVector::crossProduct(v1,v2).norm();

    v1 = TNVector::subtract(p4,p3);
    v2 = TNVector::subtract(p2,p3);
    n3 = TNVector::crossProduct(v1,v2).norm();

    v1 = TNVector::subtract(p1,p4);
    v2 = TNVector::subtract(p3,p4);
    n4 = TNVector::crossProduct(v1,v2).norm();

    useMat = true;

    //Looking from front
    /*
      p1     p4



      p2     p3
    */
}

TNQuad::~TNQuad()
{
    //dtor
}

void TNQuad::render(){
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    GLenum err = glGetError();
    if(textureId){
        glBindTexture( GL_TEXTURE_2D, textureId);
        err = glGetError();
        OPENGL_ERROR_CHECK();
    }

    if(useMat){
        material.render();
    }

    glBegin(GL_QUADS);
        glNormal3f(n1.x(),n1.y(),n1.z());
        if(textureId) glTexCoord2f(0, 0); else glColor3f(   1.0f,  1.0f,  1.0f );
        glVertex3f(p1.x(), p1.y(), p1.z());

        glNormal3f(n2.x(),n2.y(),n2.z());
        if(textureId) glTexCoord2f(1, 0); else glColor3f(   1.0f,  1.0f,  1.0f );
        glVertex3f(p2.x(), p2.y(), p2.z());

        glNormal3f(n3.x(),n3.y(),n3.z());
        if(textureId) glTexCoord2f(1, 1); else glColor3f(   1.0f,  1.0f,  1.0f );
        glVertex3f(p3.x(), p3.y(), p3.z());

        glNormal3f(n4.x(),n4.y(),n4.z());
        if(textureId) glTexCoord2f(0, 1); else glColor3f(   1.0f,  1.0f,  1.0f );
        glVertex3f(p4.x(), p4.y(), p4.z());
    glEnd();
    err = glGetError();
    OPENGL_ERROR_CHECK();

    if(textureId){
        glBindTexture( GL_TEXTURE_2D, 0);
        err = glGetError();
        OPENGL_ERROR_CHECK();
    }

    glFlush();
}

