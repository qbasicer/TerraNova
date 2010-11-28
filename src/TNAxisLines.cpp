#include "TNAxisLines.h"

#include <GL/gl.h>
#include <GL/glu.h>

TNAxisLines::TNAxisLines(TNPoint loc)
{
    this->loc = loc;
}

TNAxisLines::~TNAxisLines()
{
    //dtor
}


void TNAxisLines::render(){

    glBegin(GL_LINES);
        glColor3f(1.0f,  0.0f,  0.0f );
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(1.0,0.0,0.0);

        glColor3f(0.0f,  1.0f,  0.0f );
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,1.0,0.0);

        glColor3f(0.0f,  0.0f,  1.0f );
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,0.0,1.0);
    glEnd();
}
