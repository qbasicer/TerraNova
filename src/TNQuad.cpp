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
    TNVector cross;
    v1 = TNVector::subtract(p2,p1);
    v2 = TNVector::subtract(p4,p1);



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
    //glLoadIdentity( );
    //glTranslatef( -1.5f, 0.0f, -6.0f );
    //glColor3f(0.0,0.75,0.0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    GLenum err = glGetError();
    if(textureId){
        glBindTexture( GL_TEXTURE_2D, textureId);
        err = glGetError();
        OPENGL_ERROR_CHECK();
    }
    glBegin(GL_QUADS);
        if(textureId) glTexCoord2f(0, 0); else glColor3f(   1.0f,  0.0f,  0.0f );
        glVertex3f(p1.x(), p1.y(), p1.z());
        if(textureId) glTexCoord2f(1, 0); else glColor3f(   0.0f,  1.0f,  0.0f );
        glVertex3f(p2.x(), p2.y(), p2.z());
        if(textureId) glTexCoord2f(1, 1); else glColor3f(   0.0f,  0.0f,  1.0f );
        glVertex3f(p3.x(), p3.y(), p3.z());
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

