#ifndef TNUTIL_H_INCLUDED
#define TNUTIL_H_INCLUDED

#include <TNPoint.h>

TNPoint lerp(TNPoint a, TNPoint b, float perc);
int calcSleeptime(int elapsed, int sleepTime, int frames, int lframes, int tframes);

#define SIN_DEG(x)  (sin(x * 0.0174532925))
#define COS_DEG(x)  (cos(x * 0.0174532925))

#endif // TNUTIL_H_INCLUDED
