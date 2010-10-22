#ifndef TNOBJECT_H
#define TNOBJECT_H


class TNObject
{
    public:
        TNObject();
        virtual ~TNObject();
        virtual void render() = 0;
    protected:
    private:
};

#endif // TNOBJECT_H
