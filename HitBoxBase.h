#pragma once
#include "Structs.h"
#include <vector>
class HitBox : public virtual GameObjBase
{
public:
	HitBox(){
		type |= HITBOX_TYPE;
	};
	~HitBox(){};
	virtual bool isInside(HitBox* other){
		if (!active){
			return false;
		}
		Vec3 distance = *(other->position) - *position;
		float magSqr = distance.x*distance.x + distance.y*distance.y + distance.z*distance.z;
		float minDist = (rad + other->rad)*(rad + other->rad);
		if (magSqr < minDist){
			hitThisFrame.push_back(other);
			return true;
		}
		return false;
	}

	virtual void setStatus(bool status){
		active = status;
	}
	virtual void updateHitbox(){};
	void clearHitList(){
		hitThisFrame.clear();
	}
	Vec3* getPosition(){
		return position;
	}
	float getRadius(){
		return rad;
	}
protected:
	Vec3* position;
	float rad;
	bool active = true;
	std::vector<HitBox*> hitThisFrame;
private: 

};

