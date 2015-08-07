#pragma once
#include "PlaneDrawable.h"
#include "PhysObjBase.h"
#include "HitBoxBase.h"
class Ship : public PlaneDrawable, public PhysObjBase, public HitBox
{
public:
	Ship();
	Ship(wchar_t* regTxt, wchar_t* normTxt, Vec3* pos){
		rTxt = regTxt;
		nTxt = normTxt;
		displace(pos->x,pos->y,pos->z);
	}
	~Ship();
	const virtual Vec3* getPosition();
	
	virtual void draw(float dt);
	virtual void updateHitbox();

	void setShipTexture(ShipTexture* texture){
		shipTxt = *texture;
	}
protected:
	ShipTexture shipTxt;
	std::wstring rTxt;
	std::wstring nTxt;
};

