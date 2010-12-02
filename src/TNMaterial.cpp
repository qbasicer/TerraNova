#include "TNMaterial.h"

#include <GL/glu.h>

TNMaterial::TNMaterial()
{
    /* Default material */
    setAmbient(0.24725f, 0.1995f, 0.0745f, 1.0f);
    setDiffuse(0.75164f, 0.60648f, 0.22648f, 1.0f);
    setSpecular(0.628281f, 0.555802f, 0.366065f, 1.0f);
    setShiny(51.2f);
    //ctor
}

TNMaterial::~TNMaterial()
{
    //dtor
}

void TNMaterial::render(){
    GLfloat mat_ambient[] = { mAmbient[0],mAmbient[1],mAmbient[2],mAmbient[3]};
    GLfloat mat_diffuse[] = { mDiffuse[0],mDiffuse[1],mDiffuse[2],mDiffuse[3]};
    GLfloat mat_specular[] = { mSpecular[0],mSpecular[1],mSpecular[2],mSpecular[3]};
    GLfloat mat_shininess[] = { mShiny};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}


void TNMaterial::setAmbient(float r,  float g, float b, float a){
    mAmbient[0] = r;
    mAmbient[1] = g;
    mAmbient[2] = b;
    mAmbient[3] = a;
}
void TNMaterial::setSpecular(float r,  float g, float b, float a){
    mSpecular[0] = r;
    mSpecular[1] = g;
    mSpecular[2] = b;
    mSpecular[3] = a;
}
void TNMaterial::setDiffuse(float r,  float g, float b, float a){
    mDiffuse[0] = r;
    mDiffuse[1] = g;
    mDiffuse[2] = b;
    mDiffuse[3] = a;

}
void TNMaterial::setShiny(float s){
    mShiny = s;
}
