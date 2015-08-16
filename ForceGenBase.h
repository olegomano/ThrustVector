#pragma once
#include "PhysObjBase.h"
#include "Structs.h"
#include "GameObjBase.h"
#define GRAVITY_CONSTANT 6.673E-11
class ForceGenBase : public virtual GameObjBase{
public:
	ForceGenBase(){
		type |= FORCEGEN_TYPE;
	};
	virtual void applyForce(PhysObjBase* target) = 0;
	virtual Vec3* getPosition(){ return nullptr; };
protected:
private:
};