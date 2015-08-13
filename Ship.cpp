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

void Ship::resolveCollisions(float dt){
	if (collisionList.size() > 1){
		int colls = 2;
	}
	for (unsigned int i = 0; i < collisionList.size(); i++){
		collision col = collisionList[i];
		if (col.resolved) continue;
		
		PhysObjBase* other = col.obj1;
		PhysObjBase* me = col.obj2;
		if (checkCollision(other)){ //collision might have ben resolved already
			Vec3 mOrigin = *const_cast<Vec3*>(me->getFramePos());
			Vec3 oOrigin = *const_cast<Vec3*>(other->getFramePos());
			Vec3 dOrigin = mOrigin - oOrigin;
			Vec3 dVel = me->getVelocity() - other->getVelocity();
			Vec3 dDVDOM = dOrigin * dVel;

			Vec3 dVelSQ = dVel*dVel;
			Vec3 dOrigSq = dOrigin*dOrigin;

			double sumDO = dOrigin.x + dOrigin.y + dOrigin.z;
			double sumDV = dVel.x + dVel.y + dVel.z;

			double sumDOSq = dOrigSq.x + dOrigSq.y + dOrigSq.z;
			double sumDVSq = dVelSQ.x + dVelSQ.y + dVelSQ.z;

			double sumDVDO = dDVDOM.x + dDVDOM.y + dDVDOM.z;

			double idealDistance = me->getRadious() + other->getRadious();
			double distance = vecMagSqr(&dOrigin);
			idealDistance *= idealDistance;

			if (sumDV == 0){
				Vec3 nVel;
				me->setVelocity(nVel);
				other->setVelocity(nVel);
				continue;
			}
			

			Point res = solveQuadratic(sumDVSq, sumDVDO * 2, sumDOSq - idealDistance);
			double rRes = res.x < 0 ? res.x : res.y;
			if (-rRes > dt*3){
				continue;
			}

			me->move(rRes);
			other->move(rRes);
			Vec3 newVel = (getVelocity()*getMass() + other->getVelocity()*other->getMass()) / (getMass() + other->getMass());
			Vec3 mOldVel = getVelocity();
			Vec3 oOldVel = other->getVelocity();
			Vec3 mAccel = (newVel - mOldVel) / dt;
			Vec3 oAccel = (newVel - oOldVel) / dt;
			Vec3 mForce = mAccel * mass;
			Vec3 oForce = oAccel * other->getMass();
			me->setVelocity(newVel);
			other->setVelocity(newVel);
			me->applyForce(&mForce);
			other->applyForce(&oForce);
			me->calculateVelocity(dt);
			other->calculateVelocity(dt);

			me->setCollisionResolved(&col);
			other->setCollisionResolved(&col);
		}
	}
}

bool Ship::checkCollision(PhysObjBase* other){
	return PhysObjBase::checkCollision(other);
}



Ship::~Ship()
{
}
