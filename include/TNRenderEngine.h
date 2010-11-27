#ifndef TNRENDERENGINE_H
#define TNRENDERENGINE_H


#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

class TNRenderEngine;

#include <vector>
#include "TNObject.h"
#include "TNCamera.h"
#include "TNThread.h"
#include "TNManager.h"

using namespace std;

class TNRenderEngine : public TNThread
{
    public:
        TNRenderEngine(TNManager *manager);
        virtual ~TNRenderEngine();
        void init();
        void render();
        void addObject(TNObject *obj);
        void setCamera(TNCamera *cam){camera = cam;}
        int resizeWindow(int width, int height);
        void bounce(){run();}
        int getScreenWidth(){return width;}
        int getScreenHeight(){return height;}
        void pitchBy(double y){camera->setPitch(camera->getPitch() + y);}
        void yawBy(double x){camera->setYaw(camera->getYaw() + x);}
    protected:
        virtual void run();
    private:
        vector<TNObject*> objects;
        TNCamera *camera;

        SDL_Surface *surface;
        int width;
        int height;
        TNManager *manager;
};

#endif // TNRENDERENGINE_H
