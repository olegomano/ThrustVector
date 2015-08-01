#pragma once
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include "Structs.h"
#include "PhysObj.h"
class Plane
{
public:
	Plane();
	HRESULT				 allocBuffers(ID3D11Device* pd3dDevice);
	void				 draw(ID3D11DeviceContext*  context);
	void				 setShader(Shader shader);
	void				 rotateAboutCenter(float x, float y, float z);
	void				 setScale(float x, float y, float z){
		scale[0] = x;
		scale[1] = y; 
		scale[2] = z;
	}

	void				mulScale(float x, float y, float z){
		scale[0] *= x;
		scale[1] *= y;
		scale[2] *= z;
	}

	void applyTransform(DirectX::XMMATRIX* transform){
		modelMatrix *= *transform;
	}

	DirectX::XMMATRIX* getModelMat(){
		return &modelMatrix;
	}

	~Plane();

private:
	float scale[4];
	DirectX::XMMATRIX	 modelMatrix;
	ID3D11Buffer*		 pVertexBuffer;
	ID3D11Buffer*		 pIndexBuffer;
	UINT stride;
	UINT offset;
	Shader shader;
};

