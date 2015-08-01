#pragma once
#include "Structs.h"
#include "PhysObj.h"
class ForceGenerator
{
public:
	ForceGenerator();
	~ForceGenerator();
	virtual void applyForceOn(PhysObj* obj);
	Vec3* getPosition();
};

