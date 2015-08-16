#include "Planet.h"



void Planet::applyForce(PhysObjBase* target){
	if (target->getType() == getType()) return;

	float distance = getDistance(getPosition(), target->getPosition());
	if (distance < (getHitboxRad() + target->getHitboxRad())*.95){
		Vec3 nVel;
		target->setVelocity(nVel);
		return;
	}
	Vec3 fVec = *getPosition() - *const_cast<Vec3*>( target->getPosition() );
	Vec3 fUnit = tUnitVec(&fVec);
	Vec3 fGravity = fUnit*GRAVITY_CONSTANT*(mass*target->getMass()) / (distance*distance);
	target->applyForce(&fGravity);
	//PhysObjBase::applyForce(&fGravity);
}

Planet::~Planet()
{
}
