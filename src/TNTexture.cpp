#include "TNTexture.h"

#include <iostream>

using namespace std;

#define OPENGL_ERROR_CHECK()    if(err != GL_NO_ERROR)  cerr << "glError: " << gluErrorString(err) << endl;

TNTexture::TNTexture(string name, const char* file, GLuint id)
{
    SDL_Surface *texture = NULL;
    if(file){
        texture = SDL_LoadBMP(file);
    }
    textureId = id;

    GLenum err = glGetError();
    OPENGL_ERROR_CHECK();

    if(texture){
        textureName = name;
        glGenTextures(1, &textureId);
        if(textureId == 0){
            cerr << "Failed to generate texture ID"<< endl;
        }

        err = glGetError();
        OPENGL_ERROR_CHECK();

        glBindTexture(GL_TEXTURE_2D, textureId);

        err = glGetError();
        OPENGL_ERROR_CHECK();

        glTexImage2D( GL_TEXTURE_2D, 0, 3, texture->w,texture->h, 0, GL_BGR, GL_UNSIGNED_BYTE, texture->pixels );

        err = glGetError();
        OPENGL_ERROR_CHECK();

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

        err = glGetError();
        OPENGL_ERROR_CHECK();

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

        err = glGetError();
        OPENGL_ERROR_CHECK();
        //SDL_FreeSurface(texture);
        cout << "Bound "<<name<<" from " << file << " to " << textureId << " (" << texture->w << "x" << texture->h << ")" <<endl;
	}else{
        cerr << "Failed to load texture named "<<name<< " from "<<file<<endl;
    }

}

TNTexture::~TNTexture()
{
    //dtor
}
