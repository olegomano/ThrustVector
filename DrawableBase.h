#pragma once
#include "Structs.h"

class DrawableBase{
public:
	DrawableBase(){};
	virtual void create(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader){
		DrawableBase::pd3dDevice = pd3dDevice;
		DrawableBase::context = context;
		DrawableBase::shader = shader;
	}
	virtual void draw(float dt) = 0;
	~DrawableBase(){};
protected:
	ID3D11Device* pd3dDevice;
	ID3D11DeviceContext*  context;
	Shader* shader;
private:



};