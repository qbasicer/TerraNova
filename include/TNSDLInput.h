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
    private:
};

#endif // TNSDLINPUT_H
