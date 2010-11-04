#ifndef TNRENDERENGINE_H
#define TNRENDERENGINE_H


#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include <vector>
#include "TNObject.h"
#include "TNCamera.h"
#include "TNThread.h"

using namespace std;

class TNRenderEngine : public TNThread
{
    public:
        TNRenderEngine();
        virtual ~TNRenderEngine();
        void init();
        void render();
        void addObject(TNObject *obj);
        void setCamera(TNCamera *cam){camera = cam;}
        int resizeWindow(int width, int height);
        void bounce(){run();}
    protected:
        virtual void run();
    private:
        vector<TNObject*> objects;
        TNCamera *camera;

        SDL_Surface *surface;
};

#endif // TNRENDERENGINE_H
