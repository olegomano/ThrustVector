#pragma once
#include "Structs.h"
class PhysObj
{
public:
	PhysObj();
	virtual void		applyForce(Vec3* f);
	virtual void		calculateDisplace(float dt);
	virtual void		resetForce();
	Vec3*				getForce();
	Vec3*				getVelocity();
	virtual Vec3*		getPosition();
	float				getMass();
	~PhysObj();
protected:
	Vec3				appliedForce;
	Vec3				velocity;
	Vec3				prevVelocity;
	Vec3				position;
	float				mass = 1;
};

