#include "PlaneDrawable.h"

bool alloced = false;
ID3D11Buffer* pPlaneVertexBuffer = nullptr;
ID3D11Buffer* getPlaneVertexBuffer(ID3D11Device* pd3dDevice){
	if (!alloced){
		DirectX::XMFLOAT3 vertices[] =
		{
			DirectX::XMFLOAT3(-.5f, -.5f, 0.0f), //lb
			DirectX::XMFLOAT3(-.5f, .5f, 0.0f), //lt
			DirectX::XMFLOAT3(.5f, .5f, 0.0f), //rt

			DirectX::XMFLOAT3(-.5f, -.5f, 0.0f), //lb
			DirectX::XMFLOAT3(.5f, .5f, 0.0f), //rt
			DirectX::XMFLOAT3(.5f, -.5f, 0.0f), //rb
		};
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(DirectX::XMFLOAT3) * 6;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertices;
		pd3dDevice->CreateBuffer(&bd, &InitData, &pPlaneVertexBuffer);
		alloced = true;
	}
	return pPlaneVertexBuffer;
}

PlaneDrawable::PlaneDrawable()
{
}

void PlaneDrawable::create(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader){
	DrawableBase::create(pd3dDevice, context, shader);
	pVertexBuffer = getPlaneVertexBuffer(pd3dDevice);
}



PlaneDrawable::~PlaneDrawable()
{
}
