#pragma once
#include "PlaneDrawable.h"
#include "PhysObjBase.h"
class Ship : public PlaneDrawable, public PhysObjBase
{
public:
	Ship(){
		type |= SHIP_TYPE;
		hitBoxRad = .40f;
		mass = 1000000;
		momentInertia = mass*hitBoxRad*hitBoxRad;
	}

	Ship(const wchar_t* regTxt, const wchar_t* normTxt, Vec3* pos){
		rTxt = regTxt;
		nTxt = normTxt;
		PlaneDrawable::displace(pos->x, pos->y, pos->z);
		type |= SHIP_TYPE;
		hitBoxRad = .40f;
		mass = 1000000;
		momentInertia = mass*hitBoxRad*hitBoxRad;
	}

	~Ship();
	const virtual Vec3* getPosition();

	virtual void draw(float dt);
	bool checkCollision(PhysObjBase* other);
	void setShipTexture(ShipTexture* texture){
		shipTxt = *texture;
	}

	virtual void move(float dt){
		Vec3 nPos = *const_cast<Vec3*>(getPosition()) + getVelocity() * dt;
		setPosition(nPos.x, nPos.y, nPos.z);
	}

	virtual void setScale(float x, float y, float z){
		PlaneDrawable::setScale(x, y, z);
		hitBoxRad = x;
	}

	virtual void mulScale(float x, float y, float z){
		PlaneDrawable::mulScale(x, y, z);
		hitBoxRad *= x;
	}

	virtual Vec3* getForward(){
		forward.x = mMatrix._21;
		forward.y = mMatrix._22;
		forward.z = mMatrix._23;
		return &forward;
	}

protected:
	Vec3 forward;
	ShipTexture shipTxt;
	std::wstring rTxt;
	std::wstring nTxt;
};

