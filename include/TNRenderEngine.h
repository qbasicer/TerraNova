#ifndef TNRENDERENGINE_H
#define TNRENDERENGINE_H

#include <vector>
#include "TNObject.h"
#include "TNCamera.h"

using namespace std;

class TNRenderEngine
{
    public:
        TNRenderEngine();
        virtual ~TNRenderEngine();
        void init();
        void render();
        void addObject(TNObject *obj);
        void setCamera(TNCamera *cam){camera = cam;}
    protected:
    private:
        vector<TNObject*> objects;
        TNCamera *camera;
};

#endif // TNRENDERENGINE_H
