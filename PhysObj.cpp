#include "PhysObj.h"


PhysObj::PhysObj()
{
}

void PhysObj::applyForce(Vec3* f){
	appliedForce = appliedForce + *f;
}

void PhysObj::calculateDisplace(float dt, Vec3* out){
	prevVelocity = velocity;
	velocity = velocity + ( (appliedForce / mass)*dt);
	*out = velocity*dt;
	resetForce();
}

void PhysObj::resetForce(){
	appliedForce.x = 0;
	appliedForce.y = 0;
	appliedForce.z = 0;
}

inline Vec3* PhysObj::getForce(){
	return &appliedForce;
}

inline float PhysObj::getMass(){
	return mass;
}


PhysObj::~PhysObj()
{
}
