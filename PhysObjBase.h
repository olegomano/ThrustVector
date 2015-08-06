#pragma once
#include "Structs.h"
#include <vector>
class PhysObjBase{
public:
	PhysObjBase();
	void applyForce(Vec3* force){
		PhysObjBase::force = PhysObjBase::force + (*force);
	}
	void calculateVelocity(float dt){
		Vec3 acceleration = force / mass;
		velocity = velocity + acceleration*dt / 2.0f;
	}

	void resetFrame(){
		force.x = 0;
		force.y = 0;
		force.z = 0;
	}

	Vec3 getAcceleration(){
		return force / mass;
	}
	
	Vec3 getVelocity(){
		return velocity;
	}

	const virtual Vec3* getPosition() = 0;
protected:
	Vec3 force;
	Vec3 velocity;
	float mass = 1;
};