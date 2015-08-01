#pragma once
#include "Structs.h"
class PhysObjBase{
public:
	void applyForce(Vec3* force){
		PhysObjBase::force = PhysObjBase::force + (*force);
	}
	virtual Vec3* getPosition() = 0;
	void calculateDisplace(float dt);
protected:
	Vec3 force;
	Vec3 velocity;
};