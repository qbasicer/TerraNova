#include "TNTurret.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>
#include "TNUtil.h"
#include "TNProjectile.h"

#define BASE_SIZE   0.75
#define TOP_SIZE    0.50
#define BARREL_SIZE    0.1
#define BARREL_LENGTH   1.5

#include <iostream>
using namespace std;

TNTurret::TNTurret(TNPoint loc, TNManager *mgr)
{
    location = loc;
    base.setSize(BASE_SIZE);
    top.setSize(TOP_SIZE);
    barrel.setSize(BARREL_SIZE);
    rot = 0;
    manager = mgr;

    blackPlastic.setAmbient(0.0,0.0,0.0, 1.0f);
    blackPlastic.setDiffuse(0.01,0.01,0.01, 1.0f);
    blackPlastic.setSpecular(0.50,0.50,0.50, 1.0f);
    blackPlastic.setShiny(32.0f);

    fire.setAmbient(1.0,0.0,0.0, 1.0f);
    fire.setDiffuse(1.01,0.01,0.01, 1.0f);
    fire.setSpecular(1.50,0.50,0.50, 1.0f);
    fire.setShiny(100.0f);

    silver.setAmbient(0.1995f, 0.1995f, 0.1995f, 1.0f);
    silver.setDiffuse(0.50754, 0.50754, 0.50754, 1.0f);
    silver.setSpecular(0.508273, 0.508273, 0.508273, 1.0f);
    silver.setShiny(51.2);

    base.setMaterial(silver);
    top.setMaterial(silver);
    barrel.setMaterial(silver);

    barrel.getBack()->setMaterial(blackPlastic);

    lastFire = meTime();
    hasFired = 0;
	health = 50;
	ctime = meTime();

	rot = random() % 360;

	manager->newEnemy();



    //ctor
}

TNTurret::~TNTurret()
{
	manager->destroyEnemy();
    //dtor
}

//Fresh turrets can't get hurt
void TNTurret::hurt(float amt){
    if(meTime() - ctime < 5){
        return;
    }
    TNObject::hurt(amt);
    manager->getRenderEngine()->removeObject(this);
    delete this;

}

void TNTurret::render(){
	if(health <= 0){
		return;
	}

	if(ctime > 0 && meTime() - ctime > 5){
	    ctime = 0;
	    base.setMaterial(gold);
        top.setMaterial(gold);
        barrel.setMaterial(gold);
	}

    glPushMatrix();
    glTranslatef(location.x(), location.y()+(BASE_SIZE/2.0), location.z());
    base.render();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(location.x(), location.y()+(BASE_SIZE)+(TOP_SIZE/2), location.z());
    glRotatef(rot,0,1,0);
    top.render();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(location.x(), location.y()+(BASE_SIZE)+(TOP_SIZE/2), location.z());
    glRotatef(rot,0,1,0);
    glScaled(1.0,1.0,(BARREL_LENGTH)/BARREL_SIZE);
    glTranslated(0,0,BARREL_SIZE/2);
    barrel.render();
    glPopMatrix();

    //Fresh turrents don't do any rotational logic
    if(ctime > 0){
        return;
    }

    TNPoint player = manager->getRenderEngine()->getPlayer()->getLocation();
    player.setZ(-player.z());
    player.setX(-player.x());



    float opp = (location.x() - player.x()) / (location.z()  - player.z());


    float cdist = abs(location.x() - player.x()) + abs(location.z() - player.z());


    //cout << "Player is at (" << player.x() << "," << player.z() << ")" << endl;
    //cout << "Turret is at (" << location.x() << "," << location.z() << ")" << endl;
    //cout << "Delta: " << (location.x() - player.x()) << "," << (location.z()  - player.z()) << endl;

    float radians = atan(opp);
    float deg = 57.2957795*radians;

    if(location.z() > player.z()){
        deg += 180;
    }

    //clamp value
    if(deg < 0){
        deg += 360;
    }

    //Set barrel back to black
    if(hasFired && meTime() - lastFire > 0.5){
        barrel.getBack()->setMaterial(blackPlastic);
        hasFired = 0;
    }

    //Rotational logic
    //First to cases handle the wrap-around
    if(rot - deg < -180){
        rot -= 0.2;
    }else if(rot - deg > 180){
        rot += 0.2;
    }else if(rot - deg > 1 && rot > deg){
        rot -= 0.2;
    }else if(rot - deg < -1){
        rot += 0.2;
    }else if(meTime() - lastFire > 1 && cdist < 25){
        lastFire = meTime();
        hasFired = 1;
        barrel.getBack()->setMaterial(fire);
        fireGun();
    }

    //Clamp values here too
    if (rot > 360){
        rot -= 360;

    }else if(rot < 0){
        rot += 360;
    }
}

void TNTurret::fireGun(){
    TNPoint fireLoc(location.x(), location.y()+(BASE_SIZE)+(TOP_SIZE/2), location.z());
    TNVector fireVector(8*SIN_DEG(rot),0,8*COS_DEG(rot));
    TNProjectile *proj = new TNProjectile(fireLoc, fireVector,this,manager);
}



