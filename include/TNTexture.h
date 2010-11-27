#ifndef TNTEXTURE_H
#define TNTEXTURE_H


#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <string>

class TNTexture
{
    public:
        TNTexture(std::string name, const char* file, GLuint id);
        virtual ~TNTexture();
        GLuint getTextureId(){return textureId;}
        std::string getName(){return textureName;}
    protected:
    private:
        std::string textureName;
        GLuint textureId;
};

#endif // TNTEXTURE_H
