#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif


#include <unistd.h>
#include <iostream>
#include <time.h>

#include <iostream>

using namespace std;

#include "TNSDLInput.h"

TNSDLInput::TNSDLInput(TNManager *imgr):TNInputManager(imgr)
{
    //ctor
}

TNSDLInput::~TNSDLInput()
{
    //dtor
}

void TNSDLInput::run(){
    int done = 0;
    sleep(5);
    cout << "Starting input processing" << endl;
    while ( !shutdownRequested() ){
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

			case SDL_VIDEORESIZE:
			    /* handle resize event */

			    break;
			case SDL_KEYDOWN:
			    /* handle key presses */
			    //handleKeyPress( &event.key.keysym );
			    break;
			case SDL_QUIT:
			    /* handle quit requests */
			    done = 1;
			    break;
			default:
			    break;
			}
		}
		usleep(1000);

    }

    cout << "TNSDLInput shutting down" << endl;


}

