#include "TNUtil.h"
#include "TNArduinoInput.h"
#include "TNArduinoCodec.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

#define SMOOTHING   5


TNArduinoInput::TNArduinoInput(TNManager *imgr):TNInputManager(imgr)
{
    buffer = (char*)malloc(BUFER_SIZE);
    codec = NULL;

    cout << "************************" << endl;
    cout << "* Arduino Sensor Input *" << endl;
    cout << "************************" << endl;

}

TNArduinoInput::~TNArduinoInput()
{
    free(buffer);
    cout << "************************" << endl;
    cout << "* Arduino Sensor Input * STOPPED" << endl;
    cout << "************************" << endl;
}


void TNArduinoInput::avg(senvalues *v, senvalues *av){
    unsigned int ax = 0;
    unsigned int ay = 0;
    unsigned int az = 0;
    unsigned int gx = 0;
    unsigned int gy = 0;
    for(int i = 0; i < SMOOTHING; i++){
        ax += av[i].ax;
        ay += av[i].ay;
        az += av[i].az;

        gx += av[i].gx;
        gy += av[i].gy;

    }
    v->ax = (ax/SMOOTHING);
    v->ay = (ay/SMOOTHING);
    v->az = (az/SMOOTHING);

    v->gx = (gx/SMOOTHING);
    v->gy = (gy/SMOOTHING);

}

TNArduinoCodec *TNArduinoInput::waitDev(){
    struct stat buf;
    TNArduinoCodec *cod = NULL;
    cout << "Looking for device" << endl;
    while(stat("/dev/ttyUSB0", &buf) == -1){
        if(shutdownRequested()){
            return NULL;
        }
        usleep(1000);
    }
    cout << "Opening device" << endl;
    cod = new TNArduinoCodec("/dev/ttyUSB0");

    if (!cod->openDevice()){
        cout << "Failed to open Arduino input device" << endl;
        delete cod;
        return NULL;
    }
    return cod;
}

void TNArduinoInput::run(){
    codec = this->waitDev();

    cout << "Arduino start" << endl;
    senvalues v;

    senvalues av[5];
    int ptr = 0;


    int ecount = 0;
    int cycles = 0;
    int ccycle = 0;
    int sleepTime = 10000;
    usleep(100000);
    int t = time(0);
    while(!shutdownRequested()){
        if(!codec->getReading(&v)){
            ecount++;
            if(ecount > 1000){
                cout << "Failed to get a reading" << endl;
                perror("codec->getReading()");
                codec->closeDevice();

                delete codec;
                codec = NULL;
                manager->getRenderEngine()->resetScope();
                codec = this->waitDev();
                if(codec == NULL){
                    return;
                }
            }else{
                //Wait for the device to become available
                while(codec->openDevice()){
                    usleep(100000);
                }
            }
        }else{
            ecount = 0;
            if(v.d1){
                manager->getRenderEngine()->getPlayer()->fireGun();
            }

            ptr = (ptr + 1)%SMOOTHING;
            memcpy((void*)&av[ptr],(void*)&v,sizeof(senvalues));

            avg(&v,av);


            double acc = 0;


            double gacc = abs(v.gx - 307) + abs(v.gy - 307);
            gacc = gacc / 367.0;


            double aacc = (abs(v.ax - 330)/111.0 + abs(v.ay - 330)/111.0 + abs(v.az - 330)/111.0)/3.0;
            cout << "ax:" << v.ax << " ay:" << v.ay << " az:" << v.az << endl;
            acc = gacc + aacc;
            if(acc > 2.5){
                acc = 2.5;
            }

            cout << "Accuracy: " << acc << " gacc:" << gacc << " aacc:" << aacc << endl;
            manager->getRenderEngine()->setAccuracy(acc);

            double gx = v.gx - 307;
            double gy = v.gy - 306;
            //cout << "gx:" << gx << " gy:"<< gy << endl;
            if(gx < 400 && (gx > 3 || gx < -3)){
                //manager->getRenderEngine()->pitchBy(-(double)gx*0.01);
                manager->getRenderEngine()->moveCrosshairsUp((double)gx);
            }
            if(gy < 400 && (gy > 3 || gy < -3)){
                manager->getRenderEngine()->moveCrosshairsRight((double)gy);

            }


            ccycle++;
        }
		if(t != time(0)){
		    if(ccycle < 30){
		        ccycle = 30;
		    }
		    sleepTime = calcSleeptime(1, sleepTime, cycles, ccycle-5, 90);
		    if(sleepTime < 1000){
		        cerr << "*#*#*#*#*# ArduinoInput - WARNING!!! Can't keep input up! (" << sleepTime << ")" << endl;
		    }else{
		        cout << "*#*#*#*#*# Sleep time now at "<<sleepTime<< "/"<<cycles<<"fps syms:" << ccycle << endl;
		    }

		    ccycle = 0;
		    cycles = 0;
		    t = time(0);
		}
		cycles++;
		usleep(sleepTime);
    }
}
