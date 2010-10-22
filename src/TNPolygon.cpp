#include "TNPolygon.h"

TNPolygon::TNPolygon(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

TNPolygon::~TNPolygon()
{
    //dtor
}

virtual void render(){
    cvs.setColor(r3, g3, b3);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0, 0.0);
        glVertex2f(1.0, 0.0);
        glVertex2f(0.0, 1.0);
    glEnd();
}

