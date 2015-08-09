#pragma once
#include "PlaneDrawable.h"
#include "PhysObjBase.h"
#include "HitBoxBase.h"
class Ship : public PlaneDrawable, public PhysObjBase
{
public:
	Ship(){
		type |= SHIP_TYPE;
	}
	Ship(wchar_t* regTxt, wchar_t* normTxt, Vec3* pos){
		rTxt = regTxt;
		nTxt = normTxt;
		displace(pos->x,pos->y,pos->z);
		type |= SHIP_TYPE;
	}
	~Ship();
	const virtual Vec3* getPosition();
	
	virtual void draw(float dt);
	bool checkCollision(PhysObjBase* other);
	void setShipTexture(ShipTexture* texture){
		shipTxt = *texture;
	}
protected:
	ShipTexture shipTxt;
	std::wstring rTxt;
	std::wstring nTxt;
};

