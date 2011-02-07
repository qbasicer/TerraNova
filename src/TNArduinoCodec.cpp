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

int TNArduinoCodec::readData(char* vals, int len){
    if(fd >= 0){
        int rc = read(fd,vals,len);
        if(rc < 0){
            closeDevice();
        }
        return rc;
    }
    return -2;
}


