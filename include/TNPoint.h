#ifndef TNPOINT_H
#define TNPOINT_H


class TNPoint
{
    public:
        TNPoint(float x, float y, float z);
        float x(){return tx;};
        float y(){return ty;};
        float z(){return tz;};
    protected:
        float tx;
        float ty;
        float tz;
    private:
};

#endif // TNPOINT_H
