#ifndef TNUTIL_H_INCLUDED
#define TNUTIL_H_INCLUDED

#include <TNPoint.h>

TNPoint lerp(TNPoint a, TNPoint b, float perc);
int calcSleeptime(int elapsed, int sleepTime, int frames, int lframes, int tframes);

#endif // TNUTIL_H_INCLUDED
