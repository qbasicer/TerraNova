#include "TNUtil.h"
#include "TNPoint.h"
#include "TNVector.h"
#include <sys/time.h>

TNPoint lerp(TNPoint a, TNPoint b, float perc){
    return TNPoint((b.x() - a.x())*perc + a.x(),  (b.y() - a.y())*perc + a.y(), (b.z() - a.z())*perc + a.z());
}


TNVector vlerp(TNVector a, TNVector b, float perc){
    return TNVector((b.x() - a.x())*perc + a.x(),  (b.y() - a.y())*perc + a.y(), (b.z() - a.z())*perc + a.z());
}

int calcSleeptime(int elapsed, int sleepTime, int frames, int lframes, int tframes){
    if(frames > tframes){
        //Calculate amount of time sleeping
        float timePerFrame = (sleepTime * frames);
        //Time we spent rendering frames is 1 - sleepTime
        timePerFrame = 1000000 - timePerFrame;
        //How much time was spend rendering a single frame
        timePerFrame = timePerFrame / frames;
        //Now calculate how much time we'd have to spend if we were to render 60 frames
        timePerFrame = timePerFrame * tframes;
        //Now calculate how much time we'd have to sleep
        timePerFrame = 1000000 - timePerFrame;
        sleepTime = timePerFrame / tframes;


    }else if(frames < 30){
        //Calculate amount of time sleeping
        float timePerFrame = (sleepTime * frames);
        //Time we spent rendering frames is 1 - sleepTime
        timePerFrame = 1000000 - timePerFrame;
        //How much time was spend rendering a single frame
        timePerFrame = timePerFrame / frames;
        //Now calculate how much time we'd have to spend if we were to render 60 frames
        timePerFrame = timePerFrame * lframes;
        //Now calculate how much time we'd have to sleep
        timePerFrame = 1000000 - timePerFrame;
        sleepTime = timePerFrame / lframes;

        if(sleepTime < 0){
            sleepTime = 0;
        }
    //If the sleepTime is rather low right now, lets not try and modify the sleep time
    //mainly because the machine is already having a difficult time keeping up
    //and rendering too aggressively will cause problems elsewhere
    }else if((frames > lframes && frames < tframes) && sleepTime > 1000){
        sleepTime -= 100;
        if(sleepTime < 0){
            sleepTime = 0;
        }

    }
    return sleepTime;
}



double meTime(){
    struct timeval tv;
    gettimeofday(&tv, 0);
    return (1000000*tv.tv_sec+tv.tv_usec)/1.0e6;
}
