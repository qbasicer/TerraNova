#include "TNProjectile.h"



#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

TNProjectile::TNProjectile(TNPoint origin, TNVector vec, TNObject *immune, TNManager *mgr)
{
    this->origin = origin;
    this->vector = vec;
    this->manager = mgr;

    //Init the physics side of this object
    setVelocity(vec);
    setActive(true);
    setVelocity(true);
    setLocation(origin);
    ball = new TNSphere(origin, 0.05);

    fire.setAmbient(1.0,0.0,0.0, 1.0f);
    fire.setDiffuse(1.01,0.01,0.01, 1.0f);
    fire.setSpecular(1.50,0.50,0.50, 1.0f);
    fire.setShiny(100.0f);

    ball->setMaterial(fire);
    this->immune = immune;

    manager->getRenderEngine()->addObject(this);
    manager->getPhysicsEngine()->queueForAddition(this);
    enabled = 1;


}

TNProjectile::~TNProjectile()
{
    printf("Farewell :( %p better known as %p\n",(TNPhysicsObject*)this,this);
    //dtor
}

void TNProjectile::remove(){
    enabled = 0;
    manager->delayedDeletion(ball);
    manager->delayedDeletion(this);


}

void TNProjectile::physicsFrame(){
    if(!enabled){return;}
    // Recalculate physics then copy that value to the renderer
    TNPhysicsObject::physicsFrame();
    ball->setObjectLocation(loc);
    setVelocity(true);
	float dist = TNVector::subtract(loc,origin).getLength();
	if(dist > 20){
        remove();
        return;
	}else if(dist > 1){
	    manager->getRenderEngine()->getLock();

		std::vector<TNObject*> list;
		manager->getRenderEngine()->getObjectList(list);
		std::vector<TNObject*>::iterator itr;
		for(itr = list.begin(); itr != list.end(); itr++){
			TNObject *obj = *itr;
			if(obj != immune && obj != NULL){
				if(obj->getRadius() >= 0){
					if(obj->getObjectLocation().isSet()){
						TNVector v = TNVector::subtract(obj->getObjectLocation(),loc);
						if(v.getLength() < (obj->getRadius() + 0.1)){
							obj->hurt(50);

							remove();
							break;
						}
					}
				}
			}
		}
		manager->getRenderEngine()->releaseLock();
	}
    if(immune != manager->getRenderEngine()->getPlayer()){
        TNPoint play = manager->getRenderEngine()->getPlayer()->getLocation();
        play.setX(-play.x());
        play.setZ(-play.z());
        if(TNVector::subtract(loc,play).getLength() < 1){
			cout << "********" << endl;
			cout << "********" << endl;
			cout << "OUCH!!!" << endl;
			cout << "********" << endl;
			cout << "********" << endl;
            manager->getRenderEngine()->getPlayer()->hurt(50);
            remove();

        }
    }

}
