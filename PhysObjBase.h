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
		if (this == other) return false;
		collision nCollision(this, other);
		if (hasCollision(&nCollision) >= 0) return true;
		Vec3 distance = *const_cast<Vec3*>(getPosition()) - *const_cast<Vec3*>(other->getPosition());
		float distMag = distance.x*distance.x + distance.z*distance.z + distance.y*distance.y;
		float radMag = (radious + other->radious)* (radious + other->radious);
		if (distMag < radMag){
			collisionList.push_back(nCollision);
			other->collisionList.push_back(nCollision);		
			return true;
		}
		return false;
	};

	virtual void resolveCollisions(float dt){};

	virtual void move(float dt){
		
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

	void saveFrameState(){
		startFramePos = *getPosition();
		startFrameVel = velocity;
	}

	Vec3* getFramePos(){
		return &startFramePos;
	}

	Vec3* getFrameVel(){
		return &startFrameVel;
	}

	void removeFromCollisionList(){
		collisionList.pop_back();
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


	struct collision{
		PhysObjBase* obj1;
		PhysObjBase* obj2;
		bool resolved = false;

		collision(PhysObjBase* o1, PhysObjBase* o2){
			obj1 = o1;
			obj2 = o2;
		};

		bool operator==(collision c){
			if (c.obj1 == obj1 && c.obj2 == obj2){
				return true;
			}

			if (c.obj1 == obj2 && c.obj2 == obj1){
				return true;
			}
			return false;
		};

	};

	void setCollisionResolved(collision* col){
		collisionList[hasCollision(col)].resolved = true;
	}

protected:
	Vec3 force;
	Vec3 velocity;
	Vec3 startFrameVel;
	Vec3 startFramePos;
	std::vector<collision> collisionList;
	float mass = 1;
	float radious = 1;

	int hasCollision(collision* other){
		for (int i = 0; i < collisionList.size(); i++){
			if (collisionList[i] == *other){
				return i;
			}
		}
		return -1;
	}

};