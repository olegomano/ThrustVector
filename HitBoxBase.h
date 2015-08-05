#pragma once
#include "Structs.h"
class HitBox
{
public:
	HitBox();
	~HitBox();
	bool isInside(HitBox* other){
		if (!active) return false;
		if (other->bounds.r.l > bounds.r.l && other->bounds.r.r < bounds.r.r){
			
		}
		return false;
	}
	virtual void setStatus(bool status);
	virtual void updateHitbox() = 0;
protected:
	RectU bounds;
	bool active = true;
};

