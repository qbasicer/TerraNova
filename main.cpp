#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif


#include "TNRenderEngine.h"
#include "TNPolygon.h"
#include "TNSDLInput.h"
#include "TNManager.h"

#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <time.h>

#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

/* screen width, height, and bit depth */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP     16

/* Define our booleans */
#define TRUE  1
#define FALSE 0

/* This is our SDL surface */
SDL_Surface *surface;

/* function to release/destroy our resources and restoring the old desktop */
void Quit( int returnCode )
{
    /* clean up the window */
    SDL_Quit( );

    /* and exit appropriately */
    exit( returnCode );
}

/* function to reset our viewport after a window resize */
int resizeWindow( int width, int height )
{
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

    return( TRUE );
}

/* function to handle key press events */
void handleKeyPress( SDL_keysym *keysym )
{
    switch ( keysym->sym )
	{
	case SDLK_ESCAPE:
	    /* ESC key was pressed */
	    Quit( 0 );
	    break;
	case SDLK_F1:
	    /* F1 key was pressed
	     * this toggles fullscreen mode
	     */
	    SDL_WM_ToggleFullScreen( surface );
	    break;
	default:
	    break;
	}

    return;
}

/* Here goes our drawing code */
int drawGLScene( void )
{
    /* rotational vars for the triangle and quad, respectively */
    static GLfloat rtri, rquad;
    /* These are to calculate our fps */
    static GLint T0     = 0;
    static GLint Frames = 0;


    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* Move Left 1.5 Units And Into The Screen 6.0 */
    glLoadIdentity( );
    glTranslatef( -1.5f, 0.0f, -6.0f );

    /* Rotate The Triangle On The Y axis ( NEW ) */
    glRotatef( rtri, 0.0f, 1.0f, 0.0f );

    glBegin( GL_TRIANGLES );             /* Drawing Using Triangles       */
      glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
      glVertex3f(  0.0f,  1.0f,  0.0f ); /* Top Of Triangle               */
      glColor3f(   0.0f,  1.0f,  0.0f ); /* Green                         */
      glVertex3f( -1.0f, -1.0f,  0.0f ); /* Left Of Triangle              */
      glColor3f(   0.0f,  0.0f,  1.0f ); /* Blue                          */
      glVertex3f(  1.0f, -1.0f,  0.0f ); /* Right Of Triangle             */
    glEnd( );                            /* Finished Drawing The Triangle */

    /* Move Right 3 Units */
    glLoadIdentity( );
    glTranslatef( 1.5f, 0.0f, -6.0f );

    /* Rotate The Quad On The X axis ( NEW ) */
    glRotatef( rquad, 1.0f, 0.0f, 0.0f );

    /* Set The Color To Blue One Time Only */
    glColor3f( 0.5f, 0.5f, 1.0f);

    glBegin( GL_QUADS );                 /* Draw A Quad              */
      glVertex3f(  1.0f,  1.0f,  0.0f ); /* Top Right Of The Quad    */
      glVertex3f( -1.0f,  1.0f,  0.0f ); /* Top Left Of The Quad     */
      glVertex3f( -1.0f, -1.0f,  0.0f ); /* Bottom Left Of The Quad  */
      glVertex3f(  1.0f, -1.0f,  0.0f ); /* Bottom Right Of The Quad */
    glEnd( );                            /* Done Drawing The Quad    */

    /* Draw it to the screen */
    SDL_GL_SwapBuffers( );

    /* Gather our frames per second */
    Frames++;
    {
	GLint t = SDL_GetTicks();
	if (t - T0 >= 5000) {
	    GLfloat seconds = (t - T0) / 1000.0;
	    GLfloat fps = Frames / seconds;
	    printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
	    T0 = t;
	    Frames = 0;
	}
    }

    /* Increase The Rotation Variable For The Triangle ( NEW ) */
    rtri  += 0.2f;
    /* Decrease The Rotation Variable For The Quad     ( NEW ) */
    rquad -=0.15f;

    return( TRUE );
}

int main( int argc, char **argv )
{
    int done = 0;
    int isActive;

	TNManager mgr;
	TNRenderEngine re;
	TNSDLInput in(&mgr);
	mgr.setInput(&in);
	mgr.setRenderEngine(&re);

    /* initialize OpenGL */

    TNCamera cam( -1.5f, 0.0f, -6.0f );
    cam.setPitch(0);
    cam.setYaw(0);
    re.setCamera(&cam);

    TNPoint p1(0.0,1.0,0.0);
    TNPoint p2(-1.0,-1.0,0.0);
    TNPoint p3(1.0,-1.0,0.0);
    TNPolygon poly(p1,p2,p3);
    re.addObject(&poly);

    cout << "Entering event loop" << endl;

    //re.bounce();

    mgr.exec();

    cout << "Finished event loop" << endl;

    /* wait for events */
    float rot = 0;
    float sleepTime = 10000;
    int t = time(0);
    int frames = 0;
    while ( !done )
	{
	    /* handle the events in the queue */
        SDL_Event event;
	    while ( SDL_PollEvent( &event ) )
		{
		    switch( event.type )
			{
			case SDL_ACTIVEEVENT:
			    /* Something's happend with our focus
			     * If we lost focus or we are iconified, we
			     * shouldn't draw the screen
			     */
			    if ( event.active.gain == 0 )
				isActive = FALSE;
			    else
				isActive = TRUE;
			    break;
			case SDL_VIDEORESIZE:
			    /* handle resize event */
			    break;
			case SDL_KEYDOWN:
			    /* handle key presses */
			    handleKeyPress( &event.key.keysym );
			    break;
			case SDL_QUIT:
			    /* handle quit requests */
			    done = TRUE;
			    break;
			default:
			    break;
			}
		}

	    /* draw the scene */
        if(t != time(0)){
            cout << "FPS: "<<frames << " spend " << sleepTime*frames << "us sleeping" << endl;
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
            re.render();
            rot += 1;
            cam.setYaw(rot);
            SDL_GL_SwapBuffers( );
            usleep(sleepTime);
            frames++;
	    }
		//drawGLScene( );
	}

    /* clean ourselves up and exit */
    Quit( 0 );

    /* Should never get here */
    return( 0 );
}
