#pragma once
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include "Structs.h"
class Plane
{
public:
	Plane();
	HRESULT allocBuffers(ID3D11Device* pd3dDevice);
	void draw(ID3D11DeviceContext*  context);
	void setShader(Shader shader);
	DirectX::XMVECTOR getNormal();
	DirectX::XMVECTOR getUp();
	DirectX::XMVECTOR getRight();
	DirectX::XMVECTOR getOrigin();
	~Plane();

private:
	DirectX::XMMATRIX modelMatrix;
	ID3D11Buffer* pVertexBuffer;
	ID3D11Buffer* pIndexBuffer;
	UINT stride;
	UINT offset;
	Shader shader;
};

