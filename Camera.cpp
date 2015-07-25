#include "Camera.h"


Camera::Camera()
{
	mMatrix = DirectX::XMMatrixIdentity();
	mMatrix.r[3].m128_f32[2] = 1;
	perspectiveData[0] = 0;
	perspectiveData[1] = 50;
	perspectiveData[2] = 1;
	perspectiveData[3] = 0;
}

Camera::Camera(Vec3* pos){

}

void Camera::fillOutCb(cbCamera* out){
	out->camMat = mMatrix;
	for (int i = 0; i < 4; i++){
		out->perpspectiveData[i] = perspectiveData[i];
	}
}

void Camera::setFollow(DirectX::XMVECTOR* follow){
	followVector = follow;
}

void Camera::updateFrame(){
	if (followVector != nullptr){
		DirectX::XMVECTOR mPos = mMatrix.r[3];
		Vec3 force;
		force.x =  (followVector->m128_f32[0] - mPos.m128_f32[0]);
		force.y =  ( followVector->m128_f32[1] - mPos.m128_f32[1]);
		applyForce(&force);
		Vec3 displace;
		calculateDisplace(.016,&displace);
		mMatrix *= DirectX::XMMatrixTranslation(displace.x, displace.y, displace.z);
	}
}


Camera::~Camera()
{
}
