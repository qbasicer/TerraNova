#ifndef TNARDUINOINPUT_H
#define TNARDUINOINPUT_H

#include <TNInputManager.h>
#include <TNArduinoCodec.h>

#define EST_SYM_SEC 80
#define NO_CHANS    5
#define BYTES_PER_CHAN  2
#define BACKER      10
#define BUFER_SIZE (EST_SYM_SEC * NO_CHANS * BYTES_PER_CHAN * BACKER)

class TNArduinoInput : public TNInputManager
{
    public:
        TNArduinoInput(TNManager *mgr);
        virtual ~TNArduinoInput();
    protected:
        TNArduinoCodec *codec;
        char* buffer;
    private:
};

#endif // TNARDUINOINPUT_H
