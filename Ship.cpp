#include "Ship.h"



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



bool Ship::checkCollision(PhysObjBase* other){
	bool res = PhysObjBase::checkCollision(other);
	if (res){
		/*
		Vec3 displace = tUnitVec(&velocity)*-1*other->getRadious();
		Vec3 otherPosition = *const_cast<Vec3*>(other->getPosition());
		Vec3 newPosition = otherPosition + displace;
		setPosition(newPosition.x, newPosition.y, newPosition.z);
		*/
		/*
		Vec3 prevVel = velocity;
		Vec3 velDir = tUnitVec(&velocity);	
		velocity = (velocity * -1)  / (mass + other->getMass() );
		Vec3 forceGenerated = (velocity - prevVel);
		float forceMag = vecMag(&forceGenerated)*mass;
		if (forceMag != 0){
			forceGenerated = velDir * forceMag;
			other->applyForce(&forceGenerated);
			forceGenerated = forceGenerated * -1 * 2;
			applyForce(&forceGenerated);
		}
		*/
		Vec3 nullVelocity;
		other->setVelocity(nullVelocity);
		setVelocity(nullVelocity);


	}
	return res;
}



Ship::~Ship()
{
}
