#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif


#include <unistd.h>
#include <iostream>
#include <time.h>
#include "TNUtil.h"

#include <iostream>

using namespace std;

//#define USE_WAIT

#include "TNSDLInput.h"

TNSDLInput::TNSDLInput(TNManager *imgr):TNInputManager(imgr)
{
    xspeed = 0;
    yspeed = 0;
    //ctor
}

TNSDLInput::~TNSDLInput()
{
    //dtor
}

#define WSPEED	3.0

/* function to handle key press events */
void TNSDLInput::handleKeyPress( SDL_keysym *keysym, enum SDLKeyState state ){
    switch ( keysym->sym )
	{
	case SDLK_ESCAPE:
	    /* ESC key was pressed */
	    cout << "Asking manager to shutdown" << endl;
	    manager->shutdown();
	    break;
    case SDLK_w:
        if(state == SDL_KEY_UP){
            manager->getRenderEngine()->forward(0.0);
            xspeed = 0;
        }else{
            manager->getRenderEngine()->forward(WSPEED);
            xspeed = WSPEED;
        }
        break;
    case SDLK_s:
        if(state == SDL_KEY_UP){
            manager->getRenderEngine()->forward(0.0);
            xspeed = 0;
        }else{
            manager->getRenderEngine()->forward(-WSPEED);
            xspeed = -WSPEED;
        }
        break;
    case SDLK_d:
        if(state == SDL_KEY_UP){
            manager->getRenderEngine()->right(0.0);
            yspeed = 0;
        }else{
            manager->getRenderEngine()->right(WSPEED);
            yspeed = WSPEED;
        }
        break;
    case SDLK_a:
        if(state == SDL_KEY_UP){
            manager->getRenderEngine()->right(0.0);
            yspeed = 0;
        }else{
            manager->getRenderEngine()->right(-WSPEED);
            yspeed = -WSPEED;
        }
        break;
    case SDLK_r:
        if(state == SDL_KEY_DOWN){
            useMouse = !useMouse;
            if(!useMouse){
                SDL_ShowCursor(SDL_ENABLE);
            }
        }
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

	if(xspeed == 0 && yspeed == 0){
	    //manager->getRenderEngine()->setAccuracy(0.1);
	}else{
	    //manager->getRenderEngine()->setAccuracy(1.0);
	}

    return;
}

void TNSDLInput::run(){
    int done = 0;
	usleep(1000000);
    cout << "Starting input processing" << endl;
    int t = time(0);
    int cycles = 0;
    int sleepTime = 10000;
    useMouse = 1;
    SDL_ShowCursor(SDL_DISABLE);
    while ( !shutdownRequested() ){
        cycles++;
	    /* handle the events in the queue */
        SDL_Event event;

#ifndef USE_WAIT
        while ( SDL_PollEvent( &event ) )

#else
        SDL_WaitEvent(&event);
#endif
        {
		    switch(event.type){
            case SDL_MOUSEBUTTONDOWN:
                if(useMouse){
                    if(event.button.button == SDL_BUTTON_LEFT){
                        manager->getRenderEngine()->getPlayer()->fireGun();
                    }
                }else{
                    useMouse = 1;
                    int x,y,c_x,c_y;
                    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
                    SDL_GetMouseState(&x,&y);
                    SDL_WarpMouse(c_x,c_y);

                    x = -c_x + x;
                    y = -c_y + y;
                    SDL_ShowCursor(SDL_DISABLE);
                    SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
                }
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

                    x = -c_x + x;
                    y = -c_y + y;

                    SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
                    manager->getRenderEngine()->yawBy((double)x*0.1);
                    manager->getRenderEngine()->pitchBy((double)y*0.1);

                }
			case SDL_ACTIVEEVENT:
			    /* Something's happend with our focus
			     * If we lost focus or we are iconified, we
			     * shouldn't draw the screen
			     */
			     if(useMouse){
                    if(event.active.state != SDL_APPMOUSEFOCUS) {
                        if(useMouse){
                            if(event.active.gain == 1) {

                                SDL_ShowCursor(SDL_ENABLE);
                                //useMouse = 1;
                            }else{
                                SDL_ShowCursor(SDL_DISABLE);
                                //useMouse = 0;
                            }
                        }else{
                            SDL_ShowCursor(SDL_ENABLE);
                        }
                    }
                }
			case SDL_VIDEORESIZE:
                {
                    /* handle resize event */
                    int w = event.resize.w;
                    int h = event.resize.h;
                    if(w > 0 && h > 0){
                        //manager->getRenderEngine()->resizeWindow(w,h);
                    }
                    break;
                }
            case SDL_KEYUP:
                /* handle key presses */
			    handleKeyPress(&event.key.keysym, SDL_KEY_UP);
			    break;
            case SDL_KEYDOWN:
			    /* handle key presses */
			    handleKeyPress(&event.key.keysym, SDL_KEY_DOWN);
			    break;
			case SDL_QUIT:
			    /* handle quit requests */
			    done = 1;
			    break;
			default:
			    break;
			}
		}
#ifndef USE_WAIT
		if(t != time(0)){
		    sleepTime = calcSleeptime(1, sleepTime, cycles, 80, 100);
		    cycles = 0;
		    if(sleepTime < 1000){
		        cerr << "WARNING!!! Can't keep input up! (" << sleepTime << ")" << endl;
		    }
		    t = time(0);
		}
		usleep(sleepTime);
#endif

    }

    cout << "TNSDLInput shutting down" << endl;


}

