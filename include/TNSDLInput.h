#ifndef TNSDLINPUT_H
#define TNSDLINPUT_H

#include <TNInputManager.h>


class TNSDLInput : public TNInputManager
{
    public:
        TNSDLInput(TNManager *imgr);
        virtual ~TNSDLInput();


    protected:
        virtual void run();
        void handleKeyPress(SDL_keysym *keysym);
    private:
};

#endif // TNSDLINPUT_H
