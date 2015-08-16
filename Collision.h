#pragma once
#include "PhysObjBase.h"
#include "Structs.h"
class Collision
{
public:
	Collision(PhysObjBase* obj1, PhysObjBase* obj2){
		o1 = obj1;
		o2 = obj2;
		obj1Vel = o1->getVelocity();
		obj2Vel = o2->getVelocity();
		obj1Pos = *o1->getPosition();
		obj2Pos = *o2->getPosition();
	};
	
	void resolveCollision(double dt);
	~Collision(){};
private:
	double getCollisionTime(PhysObjBase* me, PhysObjBase* other);
protected:
	PhysObjBase* o1;
	PhysObjBase* o2;
	Vec3 obj1Vel;
	Vec3 obj2Vel;
	Vec3 obj1Pos;
	Vec3 obj2Pos;
};

