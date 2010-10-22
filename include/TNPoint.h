#ifndef TNPOINT_H
#define TNPOINT_H


class TNPoint
{
    public:
        TNPoint(float x, float y, float z);
        float x(){return x;};
        float y(){return y;};
        float z(){return z;};
    protected:
        float x;
        float y;
        float z;
    private:
};

#endif // TNPOINT_H
