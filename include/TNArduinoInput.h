#ifndef TNARDUINOINPUT_H
#define TNARDUINOINPUT_H

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
    private:
};

#endif // TNARDUINOINPUT_H
