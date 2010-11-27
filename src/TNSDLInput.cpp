#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif


#include <unistd.h>
#include <iostream>
#include <time.h>
#include "util.h"

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

/* function to handle key press events */
void TNSDLInput::handleKeyPress( SDL_keysym *keysym ){
    switch ( keysym->sym )
	{
	case SDLK_ESCAPE:
	    /* ESC key was pressed */
	    cout << "Asking manager to shutdown" << endl;
	    manager->shutdown();
	    break;
	case SDLK_F1:
	    /* F1 key was pressed
	     * this toggles fullscreen mode
	     */
	    //SDL_WM_ToggleFullScreen( surface );
	    break;
	default:
	    break;
	}

    return;
}

void TNSDLInput::run(){
    int done = 0;
    sleep(1);
    cout << "Starting input processing" << endl;
    int t = time(0);
    int cycles = 0;
    int sleepTime = 10000;
    int useMouse = 0;
    while ( !shutdownRequested() ){
        cycles++;
	    /* handle the events in the queue */
        SDL_Event event;

	    while ( SDL_PollEvent( &event ) )
		{
		    switch(event.type){
            case SDL_MOUSEMOTION:
                if(useMouse){
                    int x;
                    int y;
                    int c_x;
                    int c_y;

                    c_x = manager->getRenderEngine()->getScreenHeight()>>1;
                    c_y = manager->getRenderEngine()->getScreenWidth()>>1;

                    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

                    SDL_GetMouseState(&x,&y);
                    SDL_WarpMouse(c_x,c_y);

                    x = c_x - x;
                    y = c_y - y;

                    SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
                    manager->getRenderEngine()->yawBy((double)x*0.1);
                    manager->getRenderEngine()->pitchBy((double)y*0.1);

                }
			case SDL_ACTIVEEVENT:
			    /* Something's happend with our focus
			     * If we lost focus or we are iconified, we
			     * shouldn't draw the screen
			     */
                if(event.active.state != SDL_APPMOUSEFOCUS) {
                    if(event.active.gain == 1) {

                        SDL_ShowCursor(SDL_ENABLE);
                        useMouse = 0;
                    }else{
                        SDL_ShowCursor(SDL_DISABLE);
                        useMouse = 1;
                    }
                }
			case SDL_VIDEORESIZE:
			    /* handle resize event */

			    break;
			case SDL_KEYDOWN:
			    /* handle key presses */
			    handleKeyPress(&event.key.keysym);
			    break;
			case SDL_QUIT:
			    /* handle quit requests */
			    done = 1;
			    break;
			default:
			    break;
			}
		}
		if(t != time(0)){
		    sleepTime = calcSleeptime(1, sleepTime, cycles, 50, 60);
		    cout << cycles << " cycles" << endl;
		    cycles = 0;
		    t = time(0);
		}
		usleep(sleepTime);

    }

    cout << "TNSDLInput shutting down" << endl;


}

