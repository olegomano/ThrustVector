#pragma once
#include "Structs.h"
#include <vector>
class DrawableBase{
public:
	DrawableBase();
	virtual void create(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader){
		DrawableBase::pd3dDevice = pd3dDevice;
		DrawableBase::context = context;
		DrawableBase::shader = shader;
	}
	virtual void draw(float dt) = 0;
	void setTexture(Texture* t){
		txt = t;
	};
	static std::vector<DrawableBase*>* getDrawableList();
	~DrawableBase(){};
protected:
	ID3D11Device* pd3dDevice;
	ID3D11DeviceContext*  context;
	Shader* shader;
	Texture* txt;
private:



};