#ifndef TNSDLINPUT_H
#define TNSDLINPUT_H

#include <TNInputManager.h>


enum SDLKeyState{SDL_KEY_UP, SDL_KEY_DOWN};

class TNSDLInput : public TNInputManager
{
    public:
        TNSDLInput(TNManager *imgr);
        virtual ~TNSDLInput();


    protected:
        virtual void run();
        void handleKeyPress(SDL_keysym *keysym, enum SDLKeyState state );
		int useMouse;
    private:
};

#endif // TNSDLINPUT_H
