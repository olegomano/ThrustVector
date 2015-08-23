#pragma once
#include "Structs.h"
#include <vector>
#include "GameObjBase.h"
#include "TextureManager.h"
class DrawableBase : public virtual GameObjBase{
public:
	DrawableBase(){
		type = type | DRAWABLE_TYPE;
	};
	virtual void create(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader){
		DrawableBase::pd3dDevice = pd3dDevice;
		DrawableBase::context = context;
		DrawableBase::shader = shader;
	}
	virtual void draw(float dt){};
	void setTexture(std::wstring t){
		txt = t;
	};
	~DrawableBase(){};
protected:
	ID3D11Device* pd3dDevice;
	ID3D11DeviceContext*  context;
	Shader* shader;
	std::wstring txt;
private:
};