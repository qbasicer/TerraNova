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
#include "TNQuad.h"

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
	mgr.setInput(&in);
	mgr.setRenderEngine(&re);



    /* initialize OpenGL */

    TNCamera *cam = re.getCamera();
    cam->setPitch(0);
    cam->setYaw(0);

    TNPoint p1(0.0,1.0,0.0);
    TNPoint p2(-1.0,-1.0,0.0);
    TNPoint p3(1.0,-1.0,0.0);
    TNPolygon poly(p1,p2,p3);
    re.addObject(&poly);

    cout << "Entering event loop" << endl;

    //re.bounce();

    mgr.exec();

    cout << "Finished event loop" << endl;

    SDL_Quit();

    /* Should never get here */
    return( 0 );
}
