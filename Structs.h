#pragma once
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>

struct Shader{
	ID3D11VertexShader*     pVertexShader = nullptr;
	ID3D11PixelShader*      pPixelShader = nullptr;
	ID3D11Buffer*			pCbModelMatBuffer = nullptr;
	ID3D11Buffer*			pCbCameraBuffer = nullptr;
	ID3D11InputLayout*      pVertexLayout = nullptr;
};

struct Camera{
	DirectX::XMMATRIX camMat;
	DirectX::XMVECTOR prspectiveData;
};

struct cbModelData{
	DirectX::XMMATRIX modelMat;
	float scale[4];
	//float2 uv;
};
