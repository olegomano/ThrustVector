#pragma once
#include "DrawableBase.h"
#include "TransformBase.h"
#include "Structs.h"

class PlaneDrawable : public DrawableBase, TransformBase
{
public:
	PlaneDrawable();
	~PlaneDrawable();
	virtual void create(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader);
	virtual void draw(float dt){
		cbModelData updateData;
		updateData.modelMat = mMatrix;
		for (int i = 0; i < 4; i++){
			updateData.scale[i] = scale[i];
		}
		context->UpdateSubresource(shader->pCbModelMatBuffer, 0, nullptr, &updateData, 0, 0);
		context->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		context->IASetInputLayout(shader->pVertexLayout);

		context->VSSetConstantBuffers(0, 1, &shader->pCbModelMatBuffer);
		context->VSSetConstantBuffers(1, 1, &shader->pCbCameraBuffer);

		context->VSSetShader(shader->pVertexShader, nullptr, 0);
		context->PSSetShader(shader->pPixelShader, nullptr, 0);
		context->Draw(6, 0);
	}
private:
	ID3D11Buffer*		 pVertexBuffer = nullptr;
	ID3D11Buffer*		 pIndexBuffer = nullptr;
	const UINT stride = sizeof(DirectX::XMFLOAT3);
	const UINT offset = 0;
};

