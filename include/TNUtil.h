#ifndef TNUTIL_H_INCLUDED
#define TNUTIL_H_INCLUDED

#include <TNPoint.h>
#include <TNVector.h>
#include <stdint.h>

struct senvalues {
    uint16_t ax;
    uint16_t ay;
    uint16_t az;
    uint16_t gx;
    uint16_t gy;
    uint16_t d1;
};




TNPoint lerp(TNPoint a, TNPoint b, float perc);
TNVector vlerp(TNVector a, TNVector b, float perc);
int calcSleeptime(int elapsed, int sleepTime, int frames, int lframes, int tframes);
double meTime();

#define PLAYER_STARTHEALTH  500

#define SIN_DEG(x)  (sin(x * 0.0174532925))
#define COS_DEG(x)  (cos(x * 0.0174532925))

#endif // TNUTIL_H_INCLUDED
