#pragma once
#include "Structs.h"
#include <vector>
#include "GameObjBase.h"
class PhysObjBase : public virtual GameObjBase{
public:
	PhysObjBase(){
		type |= PHYSOBJ_TYPE;
	};
	void applyForce(Vec3* force){
		PhysObjBase::force = PhysObjBase::force + (*force);
	}
	void calculateVelocity(float dt){
		Vec3 acceleration = force / mass;
		velocity = velocity + acceleration*dt / 2.0f;
	}
	
	virtual bool checkCollision(PhysObjBase* other){
		if (hasCollision(other)) return false; 
		Vec3 distance = *const_cast<Vec3*>(getPosition()) - *const_cast<Vec3*>(other->getPosition());
		float distMag = distance.x*distance.x + distance.z*distance.z + distance.y*distance.y;
		float radMag = (radious + other->radious)* (radious + other->radious);
		if (distMag < radMag){
			collisionList.push_back(other);
			other->collisionList.push_back(this);
			return true;
		}
		return false;
	};

	void resetFrame(){
		force.x = 0;
		force.y = 0;
		force.z = 0;
	}

	void setVelocity(Vec3 v){
		velocity = v;
	}

	Vec3 getAcceleration(){
		return force / mass;
	}
	
	Vec3 getVelocity(){
		return velocity;
	}

	Vec3 getForce(){
		return force;
	}

	void clearCollisionList(){
		collisionList.clear();
	}

	float getMass(){
		return mass;
	}

	float getRadious(){
		return radious;
	}

	const virtual Vec3* getPosition() = 0;
protected:
	Vec3 force;
	Vec3 velocity;
	Vec3 prevVelocity;
	std::vector<PhysObjBase*> collisionList;
	float mass = 1;
	float radious = 1;

	bool hasCollision(PhysObjBase* other){
		for (int i = 0; i < collisionList.size(); i++){
			if (collisionList[i] == other){
				return true;
			}
		}
		return false;
	}
};