#pragma once
#include "Structs.h"
class TransformBase{
public:
	TransformBase(){
		DirectX::XMStoreFloat4x4(&mMatrix, DirectX::XMMatrixIdentity());
		for (int i = 0; i < 4; i++){
			scale[i] = 1;
		}
	}

	void displace(double x, double y, double z){
		origin.x += x;
		origin.y += y;
		origin.z += z;
		mMatrix._41 += x;
		mMatrix._42 += y;
		mMatrix._43 += z;

	}

	void setPosition(double x, double y, double z){
		origin.x = x;
		origin.y = y;
		origin.z = z;
		mMatrix._41 = x;
		mMatrix._42 = y;
		mMatrix._43 = z;
	}

	void rotate(double angle){
		DirectX::XMMATRIX xMatrix = DirectX::XMLoadFloat4x4(&mMatrix);
		xMatrix *= DirectX::XMMatrixRotationZ(angle);
		DirectX::XMStoreFloat4x4(&mMatrix, xMatrix);
	}

	void rotateCenter(double angle){
		rotate(angle,  getOrigin() );
	}

	void rotate(double angle, const Vec3* p){
		Vec3 point = *p;
		displace(-point.x, -point.y, -point.z);
		rotate(angle);
		displace(point.x, point.y, point.z);
	};

	void setNormal(Vec3* newNormal){
		DirectX::XMVECTOR nNorm;
		Vec3 up(0,0,1);
		Vec3 nRight = crossProduct(newNormal, &up);
		mMatrix._21 = newNormal->x;
		mMatrix._22 = newNormal->y;
		mMatrix._23 = newNormal->z;

		mMatrix._11 = nRight.x;
		mMatrix._12 = nRight.y;
		mMatrix._13 = nRight.z;
	}

	void mulScale(float x, float y, float z){
		scale[0] *= x;
		scale[1] *= y;
		scale[2] *= z;
	}
	virtual void setScale(float x, float y, float z){
		scale[0] = x;
		scale[1] = y;
		scale[2] = z;
	}

	const float* getScale(){
		return scale;
	}

	Vec3* getOrigin(){
	//	origin.x = mMatrix.r[3].m128_f32[0];
	//	origin.y = mMatrix.r[3].m128_f32[1];
	//	origin.z = mMatrix.r[3].m128_f32[2];
		return &origin;
	}
protected:
	DirectX::XMFLOAT4X4 mMatrix;
	float scale[4];
private:
	Vec3 origin;

};