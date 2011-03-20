#ifndef TNARDUINOCODEC_H
#define TNARDUINOCODEC_H

#include <string>


#define EST_SYM_SEC 80
#define NO_CHANS    5
#define BYTES_PER_CHAN  2
#define BACKER      10
#define BUFER_SIZE  (EST_SYM_SEC * NO_CHANS * BYTES_PER_CHAN * BACKER)
#define RDBSIZE     (NO_CHANS*BYTES_PER_CHAN*2)

struct senvalues {
    unsigned short ax;
    unsigned short ay;
    unsigned short az;
    unsigned short gx;
    unsigned short gy;
    unsigned short d1;
};

class TNArduinoCodec
{
    public:
        TNArduinoCodec(std::string file);
        virtual ~TNArduinoCodec();

        bool openDevice();
        bool closeDevice();

        int readData(char* vals, int max);

        int getReading(senvalues *val);

    protected:
        std::string fileName;
        bool calibrate();
        void wait();
        int errs;
    private:
        int fd;
};




#endif // TNARDUINOCODEC_H
