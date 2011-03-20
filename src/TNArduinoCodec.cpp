#include "TNArduinoCodec.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

TNArduinoCodec::TNArduinoCodec(std::string file)
{
    fileName = file;
    fd = -1;
    errs = 0;
}

TNArduinoCodec::~TNArduinoCodec()
{
    //dtor
}

bool TNArduinoCodec::openDevice(){
    if(fd == -1){
		struct termios term;
		fd = open(fileName.c_str(),O_RDWR | O_NOCTTY | O_NDELAY);

		if(fd > 0){

			tcgetattr(fd, &term);

			term.c_cflag |= (CLOCAL | CREAD);
			term.c_cflag &= ~PARENB;
			term.c_cflag &= ~CSTOPB;
			term.c_cflag &= ~CSIZE;
			term.c_cflag |= CS8;


			if(cfsetispeed(&term,B9600) != 0 || cfsetospeed(&term,B9600) != 0){
				perror("cfsetispeed or cfsetospeed");
				return false;
			}

			if(tcsetattr(fd,TCSANOW,&term) != 0){
				perror("tcsetattr");
				return false;
			}

			if(write(fd,"0",1) != 1){
				perror("write to fan()");
				return false;
			}

            this->wait();

			return true;
		}

	}
	return false;
}

bool TNArduinoCodec::closeDevice(){
    if(fd >= 0){
        close(fd);
        fd = -1;
    }
    return true;
}


int TNArduinoCodec::getReading(senvalues *val){
    if(fd >= 0){
        char szBuffer[RDBSIZE];
        int rd = 0;
        char *ptr = szBuffer;
        while(rd < (NO_CHANS*BYTES_PER_CHAN+1)){
            int rdi = readData(ptr, (NO_CHANS*BYTES_PER_CHAN+1)-rd);
            if(rdi < 0){
                return false;
            }
            rd += rdi;
            usleep(1000);
            ptr = ptr + rdi;
        }
        if(szBuffer[NO_CHANS*BYTES_PER_CHAN] != '\n'){
            calibrate();

        }else{
            val->ax = (szBuffer[0]&0xFF);
            val->ax |= (szBuffer[1]&0x3F) << 8;


            val->d1 = szBuffer[1] & 0xC0;
            if(val->d1 != 0){
                val->d1 = 1;
            }

            val->ay = szBuffer[2];
            val->ay |= szBuffer[3] << 8;

            val->az = szBuffer[4];
            val->az |= szBuffer[5] << 8;

            val->gx = szBuffer[6];
            val->gx |= szBuffer[7] << 8;
            val->gx = val->gx & 0x3FF;

            val->gy = szBuffer[8];
            val->gy |= szBuffer[9] << 8;
            val->gy = val->gy & 0x3FF;
        }

        return true;
    }
    return false;
}

void TNArduinoCodec::wait(){
    do{
        printf("Waiting for device to become ready\n");
        char szBuffer[2];
        int tries = 0;
        while(read(fd,szBuffer,2) < 0){
            usleep(10000);
            tries++;
            if(tries > 1000){
                printf("Giving up on device\n");
                closeDevice();
            }
        }
    }while(!calibrate());

    printf("Device is ready\n");
}

bool TNArduinoCodec::calibrate(){
    char szBuffer[2];
    int cal = 0;
    int step = 0;
    while(!cal){
        int rdi = readData(szBuffer, 1);
        if(rdi == 1){
            if(szBuffer[0] == '\n'){
                cal = 1;
            }
            step++;
        }else if(rdi < 0){
            printf("!!! Calibration aborted\n");
            return false;
        }
        usleep(1000);
    }
    printf("Calibration completed in %d bytes\n",step);
    return true;
}


int TNArduinoCodec::readData(char* vals, int len){
    if(fd >= 0){
        int rc = read(fd,vals,len);
        if(rc < 0){
            errs++;
            if(errs > 100){
                perror("read");
                wait();
            }
        }else{
            errs = 0;
        }
        return rc;
    }
    return -2;
}


