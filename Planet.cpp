#include "Planet.h"
Planet::Planet(){
	mPlane.setScale(.1f,.1f,.1f);
}

Planet::~Planet(){

}

void Planet::applyForceOn(PhysObj* obj){
	Vec3 objPos = *obj->getPosition();
	Vec3 f = (mPosition - objPos)*.05;
	float dis = f.x*f.x + f.y*f.y + f.z*f.z;
	if (dis < .5f) dis = .5f;
	if (dis != 0){
		f =  f * (1/dis);
		obj->applyForce(&f);
	}
}

void Planet::draw(float dt){
	mPlane.draw(context);
}

Vec3* Planet::getPosition(){
	return &mPosition;
}