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
#include "TNThread.h"
#include "TNManager.h"
#include "TNPlayer.h"

using namespace std;

class TNRenderEngine : public TNThread
{
    public:
        TNRenderEngine(TNManager *manager);
        virtual ~TNRenderEngine();
        void init();
        void render();
        void addObject(TNObject *obj);
        void removeObject(TNObject *obj);

        void setCamera(TNCamera *cam){camera = cam;}
        TNCamera* getCamera(){return camera;}

        TNPlayer* getPlayer(){return player;}

        int resizeWindow(int width, int height);
        void bounce(){run();}
        int getScreenWidth(){return width;}
        int getScreenHeight(){return height;}
        void pitchBy(double y);
        void yawBy(double x);

        void forward(float dist);
        void right(float speed);

		void getObjectList(vector<TNObject*> &objList);

        void getLock();
        void releaseLock();

        pthread_t owner;
    protected:
        virtual void run();
    private:
        vector<TNObject*> objects;
        TNPlayer *player;
        TNCamera *camera;
        SDL_Surface *surface;
        int width;
        int height;
        TNManager *manager;
        pthread_mutex_t mut;
};

#endif // TNRENDERENGINE_H
