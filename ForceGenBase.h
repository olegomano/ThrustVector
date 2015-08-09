#pragma once
#include "PhysObjBase.h"
#include "Structs.h"
#include "GameObjBase.h"
class ForceGenBase : public virtual GameObjBase{
public:
	ForceGenBase(){
		type |= FORCEGEN_TYPE;
	};
	virtual void applyForce(PhysObjBase* target) = 0;
	virtual Vec3* getPosition(){};
protected:
private:
};