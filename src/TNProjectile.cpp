#include "TNProjectile.h"

#include <iostream>

using namespace std;

TNProjectile::TNProjectile(TNPoint origin, TNVector vec, TNManager *mgr)
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

    manager->getRenderEngine()->addObject(this);
    manager->getPhysicsEngine()->addObject(this);


}

TNProjectile::~TNProjectile()
{
    //dtor
}

void TNProjectile::physicsFrame(){
    // Recalculate physics then copy that value to the renderer
    TNPhysicsObject::physicsFrame();
    ball->setObjectLocation(loc);

    cout << "Dist: " << TNVector::subtract(loc,origin).getLength() << endl;

    if(TNVector::subtract(loc,origin).getLength() > 20){
        manager->getRenderEngine()->getLock();
        manager->getPhysicsEngine()->queueForRemoval(this);
        manager->getRenderEngine()->removeObject(this);



        setVelocity(false);
        manager->getRenderEngine()->releaseLock();
        delete this;
    }

}
