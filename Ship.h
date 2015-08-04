#pragma once
#include "PlaneDrawable.h"
#include "PhysObjBase.h"
class Ship : public PlaneDrawable, public PhysObjBase
{
public:
	Ship();
	~Ship();
	const virtual Vec3* getPosition();
	virtual void draw(float dt);
};

