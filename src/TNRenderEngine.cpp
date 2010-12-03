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

#define SCREEN_WIDTH    680
#define SCREEN_HEIGHT   480
#define SCREEN_BPP      24


using namespace std;

TNRenderEngine::TNRenderEngine(TNManager *manager)
{
    width = SCREEN_WIDTH;
    height = SCREEN_HEIGHT;
    camera = NULL;
    this->manager = manager;
    player = new TNPlayer();
    camera = player->getCamera();
    player->setActive(true);
    player->setVelocity(true);
    manager->getPhysicsEngine()->addObject(player);

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
GLfloat LightAmbient[]  = { 0.8f, 0.8f, 0.8f, 1.0f };
/* Diffuse Light Values */
GLfloat LightDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
/* Light Position */
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };


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
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity( );
    camera->render();
    glLightfv( GL_LIGHT1, GL_POSITION, LightPosition );
    for(unsigned int i = 0; i < objects.size();i++){
        glPushMatrix();
        objects[i]->render();
        glPopMatrix();
    }
}

void TNRenderEngine::run(){
    int t = time(0);
    unsigned long long frames = 0;
    int sleepTime = 100000;
    int isActive = 1;
    init();

    int size = 10;
    TNPoint qp1(-size,-1.0,-size);
    TNPoint qp2(-size,-1.0,size);
    TNPoint qp3(size,-1.0,size);
    TNPoint qp4(size,-1.0,-size);

    manager->getTextureManager()->addTexture("grass_small","grass_small.bmp");
    manager->getTextureManager()->addTexture("grass","grass.bmp");

    TNSubdivideQuad quad(qp1,qp2,qp3,qp4);
    quad.subdivideBy(20);

    TNTurret turret(TNPoint(0,-1,3), manager);
    addObject(&turret);

    //TNQuad quad(qp1,qp2,qp3,qp4);

    GLuint textId = manager->getTextureManager()->getTextureIdByName("grass");
    addObject(&quad);

    TNAxisLines lines(TNPoint(0,0,0));
    addObject(&lines);

    TNSphere sphereTest(TNPoint(0,0,-1),0.25);
    addObject(&sphereTest);

    quad.setTexture(textId);

    while(!shutdownRequested()){
        /* draw the scene */
        player->updateDirectionVelocity();
        if(t != time(0)){
            cout << "FPS: "<<frames << " " << ((1000000 - sleepTime*frames) / 10000) << "%" << endl;
            if(isActive && frames > 60){
                //Calculate amount of time sleeping
                float timePerFrame = (sleepTime * frames);
                //Time we spent rendering frames is 1 - sleepTime
                timePerFrame = 1000000 - timePerFrame;
                //How much time was spend rendering a single frame
                timePerFrame = timePerFrame / frames;
                //Now calculate how much time we'd have to spend if we were to render 60 frames
                timePerFrame = timePerFrame * 60;
                //Now calculate how much time we'd have to sleep
                timePerFrame = 1000000 - timePerFrame;
                sleepTime = timePerFrame / 60;

                cout << "Changing sleep to " << sleepTime << endl;
            }else if(isActive && frames < 30){
                //Calculate amount of time sleeping
                float timePerFrame = (sleepTime * frames);
                //Time we spent rendering frames is 1 - sleepTime
                timePerFrame = 1000000 - timePerFrame;
                //How much time was spend rendering a single frame
                timePerFrame = timePerFrame / frames;
                //Now calculate how much time we'd have to spend if we were to render 60 frames
                timePerFrame = timePerFrame * 30;
                //Now calculate how much time we'd have to sleep
                timePerFrame = 1000000 - timePerFrame;
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
    objects.push_back(obj);
}

void TNRenderEngine::forward(float dist){
    player->setForwardSpeed(dist);

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
