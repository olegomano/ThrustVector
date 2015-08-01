#include "PhysObj.h"


PhysObj::PhysObj()
{
}

void PhysObj::applyForce(Vec3* f){
	appliedForce = appliedForce + *f;
}

void PhysObj::calculateDisplace(float dt){
	prevVelocity = velocity;
	velocity = velocity + ( (appliedForce / mass)*dt);
	position = position + (velocity*dt);
	resetForce();
}

void PhysObj::resetForce(){
	appliedForce.x = 0;
	appliedForce.y = 0;
	appliedForce.z = 0;
}

Vec3* PhysObj::getVelocity(){
	return &velocity;
}

Vec3* PhysObj::getPosition(){
	return &position;
}

Vec3* PhysObj::getForce(){
	return &appliedForce;
}

float PhysObj::getMass(){
	return mass;
}

PhysObj::~PhysObj()
{
}
