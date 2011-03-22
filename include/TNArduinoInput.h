#ifndef TNARDUINOINPUT_H
#define TNARDUINOINPUT_H

#include "TNUtil.h"

#include <TNInputManager.h>
#include <TNArduinoCodec.h>

class TNArduinoInput : public TNInputManager
{
    public:
        TNArduinoInput(TNManager *mgr);
        virtual ~TNArduinoInput();
    protected:
        TNArduinoCodec *codec;
        virtual void run();
        char* buffer;
        void avg(struct senvalues *v, struct senvalues *av);
        TNArduinoCodec *waitDev();
    private:
};

#endif // TNARDUINOINPUT_H
