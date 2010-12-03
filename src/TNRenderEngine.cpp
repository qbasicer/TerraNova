#include "TNRenderEngine.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>

#include "TNQuad.h"
#include "TNSubdivideQuad.h"
#include "TNAxisLines.h"
#include "TNUtil.h"
#include "TNTurret.h"
#include "TNSphere.h"

#define SCREEN_WIDTH    1024
#define SCREEN_HEIGHT   768
#define SCREEN_BPP      24


using namespace std;

TNRenderEngine::TNRenderEngine(TNManager *manager)
{
    width = SCREEN_WIDTH;
    height = SCREEN_HEIGHT;
    camera = NULL;
    this->manager = manager;
    player = new TNPlayer(manager);
    camera = player->getCamera();
    player->setActive(true);
    player->setVelocity(true);
    manager->getPhysicsEngine()->addObject(player);
    pthread_mutexattr_t attr;
    pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mut,&attr);
}

TNRenderEngine::~TNRenderEngine()
{
    //dtor
}


/* Snatched from CS4745 lab */
/* double meTime(){
 *	struct timeval tv;
 *	gettimeofday(&tv, NULL);
 *	return (1000000*tv.tv_sec+tv.tv_usec)/1.0e6;
 * }
 */


void TNRenderEngine::pitchBy(double y){
    float pitch = camera->getPitch() + y;

    if(pitch > 90){
        pitch = 90;
    }else if(pitch < -90){
        pitch = -90;
    }
    camera->setPitch(pitch);
}

void TNRenderEngine::yawBy(double x){
    float yaw = camera->getYaw() + x;
    if(yaw > 360){
        yaw -= 360;
    }else if(yaw < 0){
        yaw += 360;
    }
    camera->setYaw(yaw);
}


/* Ambient Light Values */
GLfloat LightAmbient[]  = { 1.8f, 1.8f, 1.8f, 1.0f };
/* Diffuse Light Values */
GLfloat LightDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
/* Light Position */
GLfloat LightPosition[] = { 0.0f, 10.0f, 2.0f, 1.0f };


void TNRenderEngine::init(){
    /* Flags to pass to SDL_SetVideoMode */
    int videoFlags;
    /* main loop variable */
    /* this holds some info about our display */
    const SDL_VideoInfo *videoInfo;

    cout << "SDL_Init()" << endl;

    /* initialize SDL */
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
	    cerr << "Video initialization failed: " << SDL_GetError( ) << endl;
	    exit( 1 );
	}

	cout << "SDL_GetVideoInfo()" << endl;

    /* Fetch the video info */
     videoInfo = SDL_GetVideoInfo( );

     if ( !videoInfo )
	{
	    cerr << "Video query failed: " << SDL_GetError() << endl;
	    exit( 1 );
	}

    /* the flags to pass to SDL_SetVideoMode */
    videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
    videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
    videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
    videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

    /* This checks to see if surfaces can be stored in memory */
    if ( videoInfo->hw_available )
	videoFlags |= SDL_HWSURFACE;
    else
	videoFlags |= SDL_SWSURFACE;

    /* This checks if hardware blits can be done */
    if ( videoInfo->blit_hw )
	videoFlags |= SDL_HWACCEL;

    cout << "SDL_GL_SetAttribute()" << endl;

    /* Sets up OpenGL double buffering */
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    cout << "SDL_SetVideoMode()" << endl;

    /* get a SDL surface */
    surface = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
				videoFlags );

    /* Verify there is a surface */
    if ( !surface )
	{
	    fprintf( stderr,  "Video mode set failed: %s\n", SDL_GetError( ) );
	    exit( 1 );
	}

    resizeWindow( SCREEN_WIDTH, SCREEN_HEIGHT );

    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH );

    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    /* Depth buffer setup */
    glClearDepth( 1.0f );

    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );

    glEnable( GL_TEXTURE_2D );

    glDisable(GL_TEXTURE_3D);

    glEnable(GL_BLEND);

    glEnable(GL_LIGHTING);




        /* Setup The Ambient Light */
    glLightfv( GL_LIGHT1, GL_AMBIENT, LightAmbient );

    /* Setup The Diffuse Light */
    glLightfv( GL_LIGHT1, GL_DIFFUSE, LightDiffuse );

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);


    /* Position The Light */


    /* Enable Light One */
    glEnable( GL_LIGHT1 );




    glColor4f(1,0,1,0);

    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    cout << "Finished initing" << endl;
}

void TNRenderEngine::render(){
    getLock();

    if(player->getHealth() <= 0){
        cout << "*************" << endl;
        cout << "* You died! *" << endl;
        cout << "*************" << endl;
        cout << "Insert coin to play again!" << endl;

        manager->shutdown();
        return;
    }

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity( );
    camera->render();
    glLightfv( GL_LIGHT1, GL_POSITION, LightPosition );
    for(unsigned int i = 0; i < objects.size();i++){
        glPushMatrix();
        objects[i]->render();
        glPopMatrix();
    }
    releaseLock();
}

void TNRenderEngine::getObjectList(vector<TNObject*> &objList){
	getLock();
	objList = objects;
	releaseLock();
}

void TNRenderEngine::run(){
    int t = time(0);
    unsigned long long frames = 0;
    int sleepTime = 100000;
    int isActive = 1;
    init();

    int size = 20;
    TNPoint qp1(-size,-1.0,-size);
    TNPoint qp2(-size,-1.0,size);
    TNPoint qp3(size,-1.0,size);
    TNPoint qp4(size,-1.0,-size);

    manager->getTextureManager()->addTexture("grass_small","grass_small.bmp");
    manager->getTextureManager()->addTexture("grass","grass.bmp");
	manager->getTextureManager()->addTexture("rock","rock.bmp");
	manager->getTextureManager()->addTexture("sky","sky.bmp");

    TNSubdivideQuad quad(qp1,qp2,qp3,qp4);
    quad.subdivideBy(20);

	float height = 5;
	for(int i = -size; i < size; i += 5){
		TNPoint p1 (-size, -1, i);
		TNPoint p4 (-size, -1, i+height);
		TNPoint p3 (-size, -1+height, i+height);
		TNPoint p2 (-size, -1+height, i);
		TNSubdivideQuad *wall = new TNSubdivideQuad(p1,p2,p3,p4);
    	wall->subdivideBy(5);
    	GLuint textId = manager->getTextureManager()->getTextureIdByName("rock");
		wall->setTexture(textId);
		addObject(wall);
	}

	for(int i = -size; i < size; i += 5){
		TNPoint p1 (size, -1, i);
		TNPoint p2 (size, -1, i+height);
		TNPoint p3 (size, -1+height, i+height);
		TNPoint p4 (size, -1+height, i);
		TNSubdivideQuad *wall = new TNSubdivideQuad(p1,p2,p3,p4);
    	wall->subdivideBy(5);
    	GLuint textId = manager->getTextureManager()->getTextureIdByName("rock");
		wall->setTexture(textId);
		addObject(wall);
	}

	for(int i = -size; i < size; i += 5){
		TNPoint p1 (i, -1, size);
		TNPoint p4 (i+height, -1, size);
		TNPoint p3 (i+height, -1+height, size);
		TNPoint p2 (i, -1+height, size);
		TNSubdivideQuad *wall = new TNSubdivideQuad(p1,p2,p3,p4);
    	wall->subdivideBy(5);
    	GLuint textId = manager->getTextureManager()->getTextureIdByName("rock");
		wall->setTexture(textId);
		addObject(wall);
	}

	for(int i = -size; i < size; i += 5){
		TNPoint p1 (i, -1, -size);
		TNPoint p2 (i+height, -1, -size);
		TNPoint p3 (i+height, -1+height, -size);
		TNPoint p4 (i, -1+height, -size);
		TNSubdivideQuad *wall = new TNSubdivideQuad(p1,p2,p3,p4);
    	wall->subdivideBy(5);
    	GLuint textId = manager->getTextureManager()->getTextureIdByName("rock");
		wall->setTexture(textId);
		addObject(wall);
	}
	int skySize = size*3;
	TNPoint sp1(-skySize,height*(1.5),skySize);
	TNPoint sp2(skySize,height*(1.5),skySize);
	TNPoint sp3(skySize,height*(1.5),-skySize);
	TNPoint sp4(-skySize,height*(1.5),-skySize);
    TNSubdivideQuad skyq(sp1,sp2,sp3,sp4);
    skyq.subdivideBy(3);
	skyq.setTexture(manager->getTextureManager()->getTextureIdByName("sky"));
	TNMaterial sky;
	sky.setAmbient(1.0,1.0,1.0,1.0);
	sky.setSpecular(0.0,0.0,0.0,1.0);
	sky.setDiffuse(1.0,1.0,1.0,1.0);
	sky.setShiny(10.0);
	skyq.setMaterial(sky);
	addObject(&skyq);
	

    GLuint textId = manager->getTextureManager()->getTextureIdByName("grass");
    addObject(&quad);

    quad.setTexture(textId);
	double last = meTime();

    while(!shutdownRequested()){
        /* draw the scene */
        player->updateDirectionVelocity();
        if(t != time(0) || frames > 60){
			double base = meTime();
			double delta = base - last;
            cout << "FPS: "<<frames << " " << ((1000000*delta - sleepTime*frames) / 10000*delta) << "%" << endl;
            if(isActive && frames > 60){
                //Calculate amount of time sleeping
                float timePerFrame = (sleepTime * frames);
                //Time we spent rendering frames is 1 - sleepTime
                timePerFrame = 1000000*delta - timePerFrame;
                //How much time was spend rendering a single frame
                timePerFrame = timePerFrame / frames;
                //Now calculate how much time we'd have to spend if we were to render 60 frames
                timePerFrame = timePerFrame * 60;
                //Now calculate how much time we'd have to sleep
                timePerFrame = 1000000*delta - timePerFrame;
                sleepTime = timePerFrame / 60;
            }else if(isActive && frames < 30){
                //Calculate amount of time sleeping
                float timePerFrame = (sleepTime * frames);
                //Time we spent rendering frames is 1 - sleepTime
                timePerFrame = 1000000*delta - timePerFrame;
                //How much time was spend rendering a single frame
                timePerFrame = timePerFrame / frames;
                //Now calculate how much time we'd have to spend if we were to render 60 frames
                timePerFrame = timePerFrame * 30;
                //Now calculate how much time we'd have to sleep
                timePerFrame = 1000000*delta - timePerFrame;
                sleepTime = timePerFrame /30;

                if(sleepTime < 0){
                    sleepTime = 0;
                    cout << "ERROR! Can't meet deadline..." << endl;
                }
            //If the sleepTime is rather low right now, lets not try and modify the sleep time
            //mainly because the machine is already having a difficult time keeping up
            //and rendering too aggressively will cause problems elsewhere
            }else if(isActive && (frames > 30 && frames < 55) && sleepTime > 1000){
                sleepTime -= 100;
                if(sleepTime < 0){
                    sleepTime = 0;
                }

            }

            t = time(0);
			last = meTime();
            frames = 0;

        }
	    if ( isActive ){
            render();
            SDL_GL_SwapBuffers( );
            usleep(sleepTime);
            frames++;
	    }
    }
    cout << "Renderer Shutting Down" << endl;
}



void TNRenderEngine::addObject(TNObject *obj){
    getLock();
    objects.push_back(obj);
    releaseLock();
}

void TNRenderEngine::removeObject(TNObject *obj){
    getLock();
    vector<TNObject*>::iterator itr;
    for(itr = objects.begin(); itr != objects.end(); itr++){
        if(*itr == obj){
            objects.erase(itr);
            break;
        }
    }
    releaseLock();
    return;

}

void TNRenderEngine::forward(float dist){
    player->setForwardSpeed(dist);
}

void TNRenderEngine::right(float dist){
    cout << "Setting right speed to " << dist << endl;
    player->setRightSpeed(dist);
}

void TNRenderEngine::getLock(){
    pthread_mutex_lock(&mut);
}

void TNRenderEngine::releaseLock(){
    pthread_mutex_unlock(&mut);
}

/* function to reset our viewport after a window resize */
int TNRenderEngine::resizeWindow( int width, int height ){
    /* Height / width ration */
    GLfloat ratio;

    /* Protect against a divide by zero */
    if ( height == 0 )
	height = 1;

    ratio = ( GLfloat )width / ( GLfloat )height;

    /* Setup our viewport. */
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );

    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    /* Set our perspective */
    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );

    /* Reset The View */
    glLoadIdentity( );

    return 1;
}
