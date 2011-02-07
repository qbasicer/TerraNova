#ifndef TNARDUINOCODEC_H
#define TNARDUINOCODEC_H

#include <string>

class TNArduinoCodec
{
    public:
        TNArduinoCodec(std::string file);
        virtual ~TNArduinoCodec();

        bool openDevice();
        bool closeDevice();

        int readData(char* vals, int max);
    protected:
        std::string fileName;
    private:
        int fd;
};

#endif // TNARDUINOCODEC_H
