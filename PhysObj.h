#pragma once
#include "Structs.h"
class PhysObj
{
public:
	PhysObj();
	virtual void		applyForce(Vec3* f);
	virtual void		calculateDisplace(float dt, Vec3* out8);
	virtual void		resetForce();
	Vec3*				getForce();
	Vec3*				getVelocity();
	Vec3*				getOrigin();
	float				getMass();
	~PhysObj();
protected:
	Vec3				appliedForce;
	Vec3				velocity;
	Vec3				prevVelocity;
	Vec3				origin;
	float				mass = 1;
};

