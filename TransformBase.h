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
		Vec3 up(0,0,1);
		Vec3 nRight = crossProduct(newNormal, &up);
		mMatrix.r[1].m128_f32[0] = newNormal->x;
		mMatrix.r[1].m128_f32[1] = newNormal->y;
		mMatrix.r[1].m128_f32[2] = newNormal->z;

		mMatrix.r[0].m128_f32[0] = nRight.x;
		mMatrix.r[0].m128_f32[1] = nRight.y;
		mMatrix.r[0].m128_f32[2] = nRight.z;
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