#include "TNCircle.h"
#include "TNUtil.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

TNCircle::TNCircle(double x, double y, double r, int segments)
{
    this->x = x;
    this->y = y;
    this->r = r;
    this->s = segments;
    mat.setAmbient(1.0,1.0,1.0,1.0);
    mat.setDiffuse(1.0,1.0,1.0,1.0);
    mat.setShiny(0);
    mat.setSpecular(1.0,1.0,1.0,1.0);
}

TNCircle::~TNCircle()
{
    //dtor
}


void TNCircle::render(){
    mat.render();
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < s; i++){
        double deg = ((double)i / (double)s)*360.0;
        glVertex2f((r*COS_DEG(deg))+x,(r*SIN_DEG(deg))+y);
    }
    glEnd();
    glFlush();
}

