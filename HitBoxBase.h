#pragma once
#include "Structs.h"
class HitBox
{
public:
	HitBox();
	~HitBox();
	bool isInside(HitBox* other){
		if (other->bounds.r.l > bounds.r.l && other->bounds.r.r < bounds.r.r){
		
		}
		return false;
	}
	virtual void updateHitbox() = 0;
protected:
	RectU bounds;
};

