#pragma once
#include "Structs.h"
#include <vector>
class HitBox
{
public:
	HitBox(){};
	~HitBox(){};
	bool isInside(HitBox* other){
		if (!active) return false;
		if (isInside(&other->bounds.p[0]) && isInside(&other->bounds.p[1])){
			return true;
		}
		return false;
	}

	virtual void setStatus(bool status){
		active = status;
	}
	virtual void updateHitbox() = 0;
protected:
	RectU bounds;
	bool active = true;
private: 
	boolean isInside(Point* p){
		if (p->x > bounds.r.l && p->x < bounds.r.r){
			if (p->y > bounds.r.t && p->y < bounds.r.b){
				return true;
			}
		}
		return false;
	}
};

