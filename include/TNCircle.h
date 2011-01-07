#ifndef TNCIRCLE_H
#define TNCIRCLE_H

#include <TNObject.h>

/* NOTE!
 * I didn't use 'setRadius' and 'getRadius' because that conflicts
 * with TNObject's getRadius that it uses for collision detection */

class TNCircle : public TNObject
{
    public:
        TNCircle(double x, double y, double r, int segments);
        virtual ~TNCircle();
        virtual void render();
        inline void setX(double x){this->x = x;}
        inline void setY(double y){this->y = y;}
        inline void setR(double r){this->r = r;}
        inline double getX(){return x;}
        inline double getY(){return y;}
        inline double getR(){return r;}
    protected:
        double x;
        double y;
        double r;
        int s;
        TNMaterial mat;
    private:
};

#endif // TNCIRCLE_H
