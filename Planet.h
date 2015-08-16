#pragma once
#include "PlaneDrawable.h"
#include "ForceGenBase.h"
class Planet : public PlaneDrawable, public ForceGenBase, public PhysObjBase
{
public:
	Planet(){
		type |= PLANET_TYPE;
		hitBoxRad = .5f;
	};

	Planet(Vec3* pos){
		type |= PLANET_TYPE;
		hitBoxRad = .5f;
		setPosition(pos->x, pos->y, pos->z);
	}
	virtual Vec3* getPosition(){
		return const_cast<Vec3*>(PlaneDrawable::getOrigin() );
	}

	virtual void setScale(float x, float y, float z){
		PlaneDrawable::setScale(x, y, z);
		hitBoxRad = y;
	}

	virtual void mulScale(float x, float y, float z){
		PlaneDrawable::mulScale(x, y, z);
		hitBoxRad *= y;
	}

	virtual void move(double dt){}
	virtual void setVelocity(Vec3 v){}

	virtual bool checkCollision(PhysObjBase* other){
		bool res =  PhysObjBase::checkCollision(other);
		if (res){
			int b = 5;
			int a = 10;
			int c = a + b;
		}
		return res;
	}

	virtual void applyForce(PhysObjBase* target);
	~Planet();
protected:
	float mass = 500000;
};

