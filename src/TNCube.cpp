#include "TNCube.h"

#include <GL/gl.h>
#include <GL/glu.h>

TNCube::TNCube(float size)
{
    this->size = size;
}

TNCube::~TNCube()
{
    //dtor
}

#define COLOR() glColor3f(   0.75f,  0.75f,  0.75f );

void TNCube::render(){
    float hsize = size/2;
    glBegin(GL_QUADS);
        COLOR();
        glVertex3f(hsize,hsize,hsize);COLOR();
        glVertex3f(hsize,-hsize,hsize);COLOR();
        glVertex3f(hsize,-hsize,-hsize);COLOR();
        glVertex3f(hsize ,hsize,-hsize);COLOR();

        glVertex3f(-hsize,hsize,hsize);COLOR();
        glVertex3f(-hsize,-hsize,hsize);COLOR();
        glVertex3f(hsize,-hsize,hsize);COLOR();
        glVertex3f(hsize,hsize,hsize);COLOR();

        glVertex3f(-hsize,hsize,hsize);COLOR();
        glVertex3f(-hsize,-hsize,hsize);COLOR();
        glVertex3f(-hsize,-hsize,-hsize);COLOR();
        glVertex3f(-hsize,hsize,-hsize);COLOR();

        glVertex3f(-hsize,hsize,-hsize);COLOR();
        glVertex3f(hsize,hsize,-hsize);COLOR();
        glVertex3f(hsize,-hsize,-hsize);COLOR();
        glVertex3f(-hsize,-hsize,-hsize);
    glEnd();
    glFlush();
}
