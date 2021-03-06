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
#include "TNSDLInput.h"
#include "TNManager.h"
#include "TNArduinoInput.h"

#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <time.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

/* screen width, height, and bit depth */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP     16

/* Define our booleans */
#define TRUE  1
#define FALSE 0

int main( int argc, char **argv )
{

	TNManager mgr;

	TNRenderEngine re(&mgr);
	TNSDLInput in(&mgr);
	TNArduinoInput ar(&mgr);
	ar.start();
	mgr.setInput(&in);
	mgr.setRenderEngine(&re);



    /* initialize OpenGL */

    TNCamera *cam = re.getCamera();
    cam->setPitch(0);
    cam->setYaw(0);

    cout << "Entering event loop" << endl;

    //re.bounce();

    cout << "Finished event loop" << endl;
    mgr.exec();
    ar.stop();
    ar.wait();

    SDL_Quit();

    /* Should never get here */
    return( 0 );
}
