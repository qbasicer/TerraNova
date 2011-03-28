#include "TNHealthPowerup.h"
#include <iostream>

using namespace std;

TNHealthPowerup::TNHealthPowerup(TNPoint origin, TNManager *mgr)
{
    active = 1;
    rot = 0.0;
    cube = new TNCube(1,1,0.01);
    GLuint textId = mgr->getTextureManager()->getTextureIdByName("health");
    cube->getFront()->setTexture(textId);
    cube->getBack()->setTexture(textId);
    setObjectLocation(origin);
    t = time(0);
    this->mgr = mgr;

}

TNHealthPowerup::~TNHealthPowerup()
{
    //dtor
}

void TNHealthPowerup::render(){
    if(active){
        rot += 0.4;
        glTranslatef(location.x(), location.y(), location.z());
        glRotatef(rot,0,1,0);
        cube->render();
        if(time(0) - t > 30){
            active = 0;
            mgr->delayedDeletion(this);
            return;
        }

        TNPoint loc = mgr->getRenderEngine()->getPlayer()->getLocation();

        TNPoint nloc = TNPoint(-location.x(), 0, -location.z());
        TNVector v = TNVector::subtract(loc,nloc);
        if(v.getLength() < 0.5){
            mgr->getRenderEngine()->getPlayer()->hurt(-50);
            active = 0;
            mgr->delayedDeletion(this);
        }
    }
}
