#include "TNArduinoInput.h"

TNArduinoInput::TNArduinoInput(TNManager *imgr):TNInputManager(imgr)
{
    buffer = (char*)malloc(BUFER_SIZE);
}

TNArduinoInput::~TNArduinoInput()
{
    //dtor
}
