#pragma once
#include "Structs.h"
class Drawable
{
public:
	Drawable();
	virtual void create(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader){
		Drawable::pd3dDevice = pd3dDevice;
		Drawable::context = context;
		Drawable::shader = shader;
	}
	virtual void draw(float dt);
	~Drawable();
protected:
	ID3D11Device* pd3dDevice;
	ID3D11DeviceContext*  context;
	Shader* shader;
};

