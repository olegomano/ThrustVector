#pragma once
#include "Structs.h"
class TransformBase{
public:
	TransformBase(){
		mMatrix = DirectX::XMMatrixIdentity();
		for (int i = 0; i < 4; i++){
			scale[i] = 1;
		}
	}

	void displace(double x, double y, double z){
		origin.x += x;
		origin.y += y;
		origin.z += z;
		mMatrix.r[3].m128_f32[0] += x;
		mMatrix.r[3].m128_f32[1] += y;
		mMatrix.r[3].m128_f32[2] += z;

	}

	void setPosition(double x, double y, double z){
		origin.x = x;
		origin.y = y;
		origin.z = z;
		mMatrix.r[3].m128_f32[0] = x;
		mMatrix.r[3].m128_f32[1] = y;
		mMatrix.r[3].m128_f32[2] = z;
	}

	void rotate(double angle){
		mMatrix *= DirectX::XMMatrixRotationZ(angle);

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
		nNorm.m128_f32[0] = newNormal->x;
		nNorm.m128_f32[1] = newNormal->y;
		nNorm.m128_f32[2] = newNormal->z;

		//DirectX::XMVECTOR nRight = nNorm * mMatrix.r[2];
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
	DirectX::XMMATRIX mMatrix;
	float scale[4];
private:
	Vec3 origin;

};