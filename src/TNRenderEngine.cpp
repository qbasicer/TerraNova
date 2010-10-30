#include "TNRenderEngine.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

TNRenderEngine::TNRenderEngine()
{
    camera = NULL;
}

TNRenderEngine::~TNRenderEngine()
{
    //dtor
}

void TNRenderEngine::init(){
    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH );

    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    /* Depth buffer setup */
    glClearDepth( 1.0f );

    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );

    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void TNRenderEngine::render(){
    for(unsigned int i = 0; i < objects.size();i++){
        objects[i]->render();
    }
}

void TNRenderEngine::addObject(TNObject *obj){
    objects.push_back(obj);
}
