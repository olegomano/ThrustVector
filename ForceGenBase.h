#pragma once
#include "PhysObjBase.h"
#include "Structs.h"
#include "GameObjBase.h"
class ForceGenBase{
public:
	ForceGenBase(){};
	virtual void applyForce(PhysObjBase* target) = 0;
	virtual Vec3* getPosition() = 0;
protected:
private:
};