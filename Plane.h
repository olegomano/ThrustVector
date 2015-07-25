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
	void				 draw(ID3D11DeviceContext*  context, float dt);
	void				 setShader(Shader shader);
	void				 rotateAboutCenter(float x, float y, float z);

	void applyTransform(DirectX::XMMATRIX* transform){
		modelMatrix *= *transform;
	}

	DirectX::XMMATRIX* getModelMat(){
		return &modelMatrix;
	}

	~Plane();

private:
	DirectX::XMMATRIX	 modelMatrix;
	ID3D11Buffer*		 pVertexBuffer;
	ID3D11Buffer*		 pIndexBuffer;
	UINT stride;
	UINT offset;
	Shader shader;
};

