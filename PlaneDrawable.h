#pragma once
#include "DrawableBase.h"
#include "TransformBase.h"
#include "Structs.h"

class PlaneDrawable : public DrawableBase, public TransformBase
{
public:
	PlaneDrawable();
	~PlaneDrawable();
	virtual void create(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader);
	virtual void draw(float dt);
private:
	ID3D11Buffer*		 pVertexBuffer = nullptr;
	ID3D11Buffer*		 pIndexBuffer = nullptr;
	UINT stride = sizeof(DirectX::XMFLOAT3) + sizeof(float) + sizeof(float);
	UINT offset = 0;
	float uvCoords[12];
};

