#ifndef TNTEXTUREMANAGER_H
#define TNTEXTUREMANAGER_H

#include <string>
#include "TNTexture.h"
#include <vector>

class TNTextureManager
{
    public:
        TNTextureManager();
        virtual ~TNTextureManager();
        void addTexture(std::string name, const char* file);
        GLuint getTextureIdByName(std::string name);
    protected:
    private:
        std::vector <TNTexture*> textures;
        GLuint unused;
};

#endif // TNTEXTUREMANAGER_H
