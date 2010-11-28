#ifndef TNPOINT_H
#define TNPOINT_H


class TNPoint
{
    public:
        TNPoint(float x, float y, float z);
        TNPoint();
        float x(){return tx;};
        float y(){return ty;};
        float z(){return tz;};
        void set(float x, float y, float z);
        void setX(float x){tx = x;}
        void setY(float y){ty = y;}
        void setZ(float z){tz = z;}
    protected:
        float tx;
        float ty;
        float tz;
    private:
};

#endif // TNPOINT_H
