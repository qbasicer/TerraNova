#include "TNSubdivideQuad.h"

#include "TNUtil.h"

#include <iostream>

using namespace std;

TNSubdivideQuad::TNSubdivideQuad(TNPoint p1, TNPoint p2, TNPoint p3, TNPoint p4):TNQuad(p1,p2,p3,p4)
{
    divisions = 1;
}

TNSubdivideQuad::~TNSubdivideQuad()
{
    //dtor
}

void TNSubdivideQuad::subdivideBy(int divisions){
    if(divisions > 0){
        this->divisions = divisions;
    }
}

void TNSubdivideQuad::render(){
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    if(textureId){
        glBindTexture( GL_TEXTURE_2D, textureId);
    }
	material.render();
    float step = 1/(float)divisions;
    for(float i = 0; i < 1; i += step){
        for(float j = 0; j < 1; j += step){

            TNVector nsideA1 = vlerp(n1,n2,i);
            TNVector nsideA2 = vlerp(n1,n2,i+step);
            TNVector nsideB1 = vlerp(n4,n3,i);
            TNVector nsideB2 = vlerp(n4,n3,i+step);

            TNVector nl1 = vlerp(nsideA1,nsideB1,j);
            TNVector nl2 = vlerp(nsideA2,nsideB2,j);
            TNVector nl3 = vlerp(nsideA2,nsideB2,j+step);
            TNVector nl4 = vlerp(nsideA1,nsideB1,j+step);


            TNPoint sideA1 = lerp(p1,p2,i);
            TNPoint sideA2 = lerp(p1,p2,i+step);
            TNPoint sideB1 = lerp(p4,p3,i);
            TNPoint sideB2 = lerp(p4,p3,i+step);

            TNPoint l1 = lerp(sideA1,sideB1,j);
            TNPoint l2 = lerp(sideA2,sideB2,j);
            TNPoint l3 = lerp(sideA2,sideB2,j+step);
            TNPoint l4 = lerp(sideA1,sideB1,j+step);

            fastRenderQuad(l1,nl1,l2,nl2,l3,nl3,l4,nl4);

        }
    }

    if(textureId){
        glBindTexture( GL_TEXTURE_2D, 0);
    }

    glFlush();
}

void TNSubdivideQuad::fastRenderQuad(TNPoint p1,TNVector nl1, TNPoint p2, TNVector nl2, TNPoint p3, TNVector nl3, TNPoint p4,TNVector nl4){
    glBegin(GL_QUADS);
        glNormal3f(nl1.x(),nl1.y(),nl1.z());
        if(textureId) glTexCoord2f(0, 0); else glColor3f(   1.0f,  0.0f,  0.0f );
        glVertex3f(p1.x(), p1.y(), p1.z());

        glNormal3f(nl2.x(),nl2.y(),nl2.z());
        if(textureId) glTexCoord2f(1, 0); else glColor3f(   0.0f,  1.0f,  0.0f );
        glVertex3f(p2.x(), p2.y(), p2.z());

        glNormal3f(nl3.x(),nl3.y(),nl3.z());
        if(textureId) glTexCoord2f(1, 1); else glColor3f(   0.0f,  0.0f,  1.0f );
        glVertex3f(p3.x(), p3.y(), p3.z());

        glNormal3f(nl4.x(),nl4.y(),nl4.z());
        if(textureId) glTexCoord2f(0, 1); else glColor3f(   1.0f,  1.0f,  1.0f );
        glVertex3f(p4.x(), p4.y(), p4.z());
    glEnd();
}
