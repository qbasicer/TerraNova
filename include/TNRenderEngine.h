#ifndef TNRENDERENGINE_H
#define TNRENDERENGINE_H

#include <vector>
#include "TNObject.h"

using namespace std;

class TNRenderEngine
{
    public:
        TNRenderEngine();
        virtual ~TNRenderEngine();
        void init();
        void render();
        void addObject(TNObject *obj);
    protected:
    private:
        vector<TNObject*> objects;
};

#endif // TNRENDERENGINE_H
