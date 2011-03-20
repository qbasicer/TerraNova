#include "TNArduinoInput.h"
#include "TNUtil.h"
#include <iostream>

using namespace std;


TNArduinoInput::TNArduinoInput(TNManager *imgr):TNInputManager(imgr)
{
    buffer = (char*)malloc(BUFER_SIZE);
    codec = new TNArduinoCodec("/dev/ttyUSB0");

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

void TNArduinoInput::run(){
    if (!codec->openDevice()){
        cout << "Failed to open Arduino input device" << endl;
        return;
    }
    cout << "Arduino start" << endl;
    senvalues v;
    int ecount = 0;
    int cycles = 0;
    int ccycle = 0;
    int sleepTime = 10000;
    usleep(100000);
    int t = time(0);
    int target = 0;
    while(!shutdownRequested()){
        if(!codec->getReading(&v)){
            ecount++;
            if(ecount > 1000){
                cout << "Failed to get a reading" << endl;
                perror("codec->getReading()");
                codec->closeDevice();
                return;
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
            double gx = v.gx - 303;
            double gy = v.gy - 303;
            cout << "gx:" << gx << " gy:"<< gy << endl;
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
