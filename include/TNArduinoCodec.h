#ifndef TNARDUINOCODEC_H
#define TNARDUINOCODEC_H

#include <string>
#include "TNUtil.h"

#define EST_SYM_SEC 80
#define NO_CHANS    5
#define BYTES_PER_CHAN  2
#define BACKER      10
#define BUFER_SIZE  (EST_SYM_SEC * NO_CHANS * BYTES_PER_CHAN * BACKER)
#define RDBSIZE     (NO_CHANS*BYTES_PER_CHAN*2)

class TNArduinoCodec
{
    public:
        TNArduinoCodec(std::string file);
        virtual ~TNArduinoCodec();

        bool openDevice();
        bool closeDevice();

        int getReading(senvalues *val);

    protected:
        std::string fileName;
        int readData(unsigned char* vals, int max);
        bool calibrate();
        void wait();
        int errs;
    private:
        int fd;
};




#endif // TNARDUINOCODEC_H
