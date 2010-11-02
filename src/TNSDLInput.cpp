#include "TNSDLInput.h"

TNSDLInput::TNSDLInput()
{
    //ctor
}

TNSDLInput::~TNSDLInput()
{
    //dtor
}


static void *inputThread(void *clazz){
    TNSDLInput *input = (TNSDLInput*)clazz;
    int done = 0;
    while ( !done ){
	    /* handle the events in the queue */

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
			    done = TRUE;
			    break;
			default:
			    break;
			}
		}
		usleep(1000);

    }
}

