#include "Camera.h"


Camera::Camera()
{
	DirectX::XMStoreFloat4x4(&mMatrix,DirectX::XMMatrixIdentity());
	displace(0, 0, -10);
	perspectiveData[0] = 0;
	perspectiveData[1] = 1000;
	perspectiveData[2] = 1;
	perspectiveData[3] = 0;

}


Camera::Camera(Vec3* pos){

}

Vec3 camVel;
void Camera::updateCameraPosition(double dt){
	if (followObj != nullptr){
		setPosition(followObj->getPosition()->x, followObj->getPosition()->y, getOrigin()->z);
	}
}

void Camera::fillOutCb(cbCamera* out){
	DirectX::XMMATRIX asMatrix = DirectX::XMLoadFloat4x4(&mMatrix);
	//asMatrix.r[0].m128_f32[3] *= -1;
	//asMatrix.r[1].m128_f32[3] *= -1;
	//asMatrix.r[2].m128_f32[3] *= -1;
	out->camMat = DirectX::XMMatrixInverse(nullptr,asMatrix);
	for (int i = 0; i < 4; i++){
		out->perpspectiveData[i] = perspectiveData[i];
	}
}


Camera::~Camera()
{
}
