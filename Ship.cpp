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
	bool result = PhysObjBase::checkCollision(other);
	if (result){
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
		Vec3 mOrigin = *const_cast<Vec3*>(getPosition());
		Vec3 oOrigin = *const_cast<Vec3*>(other->getPosition());
		
		
		//Vec3 mDV = mOrigin * getVelocity();
		//Vec3 oDV = oOrigin * other->getVelocity();
		//Vec3 dDV = mDV - oDV;
		//double sumDDV = dDV.x + dDV.y + dDV.z;
		
		Vec3 dOrigin = mOrigin - oOrigin;
		Vec3 dVel = getVelocity() - other->getVelocity();
		Vec3 dDVDOM = dOrigin * dVel;

		Vec3 dVelSQ = dVel*dVel; 
		Vec3 dOrigSq = dOrigin*dOrigin;

		double sumDO = dOrigin.x + dOrigin.y + dOrigin.z;
		double sumDV = dVel.x + dVel.y + dVel.z;
		
		double sumDOSq = dOrigSq.x + dOrigSq.y + dOrigSq.z;
		double sumDVSq = dVelSQ.x + dVelSQ.y + dVelSQ.z;
		
		double sumDVDO = dDVDOM.x + dDVDOM.y + dDVDOM.z;


		if (sumDV == 0){
			return result;
		}
		double distance = vecMagSqr(&dOrigin);
		double idealDistance = radious + other->getRadious();
		idealDistance *= idealDistance;
		
		Point res = solveQuadratic(sumDVSq, sumDVDO * 2, sumDOSq - idealDistance);
		double rRes = res.x < 0 ? res.x : res.y;
		if (-rRes > FRAME_TIME){
			return result;
		}
		move(rRes);
		other->move(rRes);
		Vec3 newVel = (getVelocity()*getMass() + other->getVelocity()*other->getMass()) / (getMass() + other->getMass());
		
		Vec3 mOldVel = getVelocity();
		Vec3 oOldVel = other->getVelocity();
		
		Vec3 mAccel = (mOldVel - newVel)/FRAME_TIME;
		Vec3 oAccel = (oOldVel - newVel)/FRAME_TIME;
		Vec3 mForce = mAccel * mass;
		Vec3 oForce = oAccel * other->getMass();

		//applyForce(&oForce);
		//other->applyForce(&mForce);

		setVelocity(newVel);
		other->setVelocity(newVel);
		//int a = 100;
		//other->setVelocity(nullVelocity);
		//setVelocity(nullVelocity);
	
	}
	return result;
}



Ship::~Ship()
{
}
