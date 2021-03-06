#ifndef TNVECTOR_H
#define TNVECTOR_H

#include "TNPoint.h"

class TNVector
{
    public:
        TNVector(float x, float y, float z, float h = 0){tx = x;ty = y; tz = z; th = h;}
        TNVector();
        virtual ~TNVector();
        float Gettx() { return tx; }
        void Settx(float val) { tx = val; }
        float Getty() { return ty; }
        void Setty(float val) { ty = val; }
        float Gettz() { return tz; }
        void Settz(float val) { tz = val; }
        float Getth() { return th; }
        void Setth(float val) { th = val; }
        void setLength(float length);
        float getLength();

        void setx(float val){tx = val;}
        void sety(float val){ty = val;}
        void setz(float val){tz = val;}

        float x(){return tx;}
        float y(){return ty;}
        float z(){return tz;}


        TNVector norm();

        static TNVector subtract(TNPoint a, TNPoint b);
        static TNVector crossProduct(TNVector a, TNVector b);
    protected:
    private:
        float tx;
        float ty;
        float tz;
        float th;
};

#endif // TNVECTOR_H
