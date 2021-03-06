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
#include <semaphore.h>

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

        double getAccuracy(){return accuracy;}
        void setAccuracy(double acc){accuracy = acc;}

        void moveCrosshairsUp(double amt);
        void moveCrosshairsRight(double amt);

        void resetScope(){setAccuracy(0); xhh = 0.5; xhv = 0.5;}

        pthread_t owner;
    protected:
        virtual void run();

        float getFractionalHealth();
    private:
        vector<TNObject*> objects;

        double accuracy;

        TNPlayer *player;
        TNCamera *camera;
        SDL_Surface *surface;
        int width;
        int height;
        TNManager *manager;
        sem_t sem;
        pthread_mutex_t mut;
        TNMaterial healthbarmaterial;

        double xhv;
        double xhh;

        float vertclip;
        float horizclip;

};

#endif // TNRENDERENGINE_H
