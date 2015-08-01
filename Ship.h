#pragma once
#include "PhysObj.h"
#include "Plane.h"
#include "Structs.h"
#include "Drawable.h"
class Ship : public PhysObj, Drawable
{
public:
	Ship();
	void create(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader){
		Drawable::create(pd3dDevice,context,shader);
		mPlane.allocBuffers(pd3dDevice);
		mPlane.setShader(*shader);
	}
	Plane* getPlane(){
		return &mPlane;
	}
	void draw(float dt);
	~Ship();
private:
	Plane mPlane;
};

