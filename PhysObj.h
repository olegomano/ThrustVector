#pragma once
#include "Structs.h"
class PhysObj
{
public:
	PhysObj();
	virtual void		applyForce(Vec3* f);
	virtual void		calculateDisplace(float dt, Vec3* out8);
	Vec3*				getForce();
	Vec3*				getVelocity();
	float				getMass();
	~PhysObj();
protected:
	Vec3				appliedForce;
	Vec3				velocity;
	float				mass = 1;
};

