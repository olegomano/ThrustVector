#include "Ship.h"


Ship::Ship()
{
}

void Ship::draw(float dt){
	//PlaneDrawable::draw(dt);
	cbModelData updateData;
	updateData.modelMat = mMatrix;
	for (int i = 0; i < 4; i++){
		updateData.scale[i] = scale[i];
	}
	ID3D11BlendState* d3dBlendState;
	D3D11_BLEND_DESC omDesc;
	ZeroMemory(&omDesc, sizeof(D3D11_BLEND_DESC));
	omDesc.RenderTarget[0].BlendEnable = true;
	omDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	omDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	omDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	omDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	omDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	omDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	omDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	pd3dDevice->CreateBlendState(&omDesc, &d3dBlendState);
	context->OMSetBlendState(d3dBlendState, 0, 0xffffffff);

	context->UpdateSubresource(shader->pCbModelMatBuffer, 0, nullptr, &updateData, 0, 0);
	context->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetInputLayout(shader->pVertexLayout);

	context->VSSetConstantBuffers(0, 1, &shader->pCbModelMatBuffer);
	context->VSSetConstantBuffers(1, 1, &shader->pCbCameraBuffer);

	context->VSSetShader(shader->pVertexShader, nullptr, 0);
	context->PSSetShader(shader->pPixelShader, nullptr, 0);

	context->PSSetShaderResources(0, 1, &txt->ptextureResView);
	context->PSSetSamplers(0, 1, &txt->psamplerState);

	context->Draw(6, 0);
}

const Vec3* Ship::getPosition(){
	return( Vec3*)(&mMatrix.r[3]);
}

void Ship::updateHitbox(){
	Vec3 currPosition = *getPosition();
	bounds.r.l = currPosition.x - getScale()[0] / 2.0;
	bounds.r.t = currPosition.y - getScale()[1] / 2.0f;
	bounds.r.r = currPosition.x + getScale()[0] / 2.0;
	bounds.r.b = currPosition.y + getScale()[1] / 2.0f;
}

Ship::~Ship()
{
}
