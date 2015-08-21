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
		velocity = velocity + acceleration*dt;
		angularVelocity = angularVelocity + (torque / momentInertia)*dt;
		if (angularVelocity != 0){
			int a = 5;
		}
		
	}

	virtual bool checkCollision(PhysObjBase* other){
		if (this == other) return false;
		if (haveCollision(other) )return false;
		Vec3 distance = *const_cast<Vec3*>(getPosition()) - *const_cast<Vec3*>(other->getPosition());
		float distMag = distance.x*distance.x + distance.z*distance.z + distance.y*distance.y;
		float radMag = (hitBoxRad + other->hitBoxRad)* (hitBoxRad + other->hitBoxRad);
		
		int realDist = distMag * 1000;
		int realRadMag = radMag * 1000;
		
		if (distMag < radMag){
			collisionList.push_back(other);
			other->collisionList.push_back(this);		
			return true;
		}
		return false;
	};

	virtual void onCollisionResolved(PhysObjBase* collidedWith){}
		
	virtual void move(float dt){};

	virtual void applyTangentalForce(double f){
		torque += (f*hitBoxRad);
	};

	virtual void setAngularVelocuty(double vel){
		//angularVelocity = vel;
	}

	virtual void resetFrame(){
		force.x = 0;
		force.y = 0;
		force.z = 0;
		torque = 0;
	}

	virtual void setVelocity(Vec3 v){
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

	double getMass(){
		return mass;
	}

	double getHitboxRad(){
		return hitBoxRad;
	}
	const virtual Vec3* getPosition() = 0;
	
	double getElasticity(){
		return elasticity;
	}
private:
	bool haveCollision(PhysObjBase* other){
		for (unsigned int i = 0; i < collisionList.size(); i++){
			if (other == collisionList[i]){
				return true;
			}
		}
		return false;
	}

	

protected:
	Vec3 force;
	Vec3 velocity;
	Vec3 startFrameVel;
	Vec3 startFramePos;
	
	double angularVelocity = 0;
	double torque = 0;
	double mass = 10;
	double hitBoxRad = 1;
	double elasticity = .3;
	double momentInertia = mass*hitBoxRad*hitBoxRad;
	std::vector<PhysObjBase*> collisionList;

	

};