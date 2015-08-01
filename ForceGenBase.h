#pragma once
#include "PhysObjBase.h"
#include "Structs.h"

class ForceGenBase{
public:
	virtual void applyForce(PhysObjBase* target) = 0;
	virtual Vec3* getPosition() = 0;
protected:
private:
};