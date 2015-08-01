#include "Camera.h"


Camera::Camera()
{
	mMatrix = DirectX::XMMatrixIdentity();
	mMatrix.r[3].m128_f32[2] = 1;
	perspectiveData[0] = 0;
	perspectiveData[1] = 50;
	perspectiveData[2] = 1;
	perspectiveData[3] = 0;
	for (int i = 0; i < 3; i++){
		((float*)&position)[i] = mMatrix.r[3].m128_f32[i];
	}
}


Camera::Camera(Vec3* pos){

}

float Camera::getFocusDistance(){
	return perspectiveData[2];
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

}


Camera::~Camera()
{
}
