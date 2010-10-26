#ifndef TNVECTOR_H
#define TNVECTOR_H


class TNVector
{
    public:
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
    protected:
    private:
        float tx;
        float ty;
        float tz;
        float th;
};

#endif // TNVECTOR_H
