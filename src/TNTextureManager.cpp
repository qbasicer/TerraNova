#include "TNTextureManager.h"

#include <iostream>
using namespace std;

TNTextureManager::TNTextureManager()
{
    unused = 1000;
    addTexture("none",NULL);
}

TNTextureManager::~TNTextureManager()
{
    //dtor
}


void TNTextureManager::addTexture(std::string name, const char* file){
    TNTexture *tex = new TNTexture(name, file,unused++);
    if(tex->getTextureId() != 0){
        textures.push_back(tex);
    }
}


GLuint TNTextureManager::getTextureIdByName(std::string name){
    for(unsigned int i = 0; i < textures.size(); i++){
        if(textures[i]->getName() == name){
            return textures[i]->getTextureId();
        }
    }
    cerr << "Texture '"<<name<<"' could not be found." << endl;
    return 0;

}
