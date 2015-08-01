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

	void displace(float x, float y, float z){
		mMatrix.r[3].m128_f32[0] += x;
		mMatrix.r[3].m128_f32[1] += y;
		mMatrix.r[3].m128_f32[2] += z;

	}
	void rotate(float angle){
		mMatrix *= DirectX::XMMatrixRotationZ(angle);
	}
	void rotate(float angle, float point){

	};

	void mulScale(float x, float y, float z){
		scale[0] *= x;
		scale[1] *= y;
		scale[2] *= z;
	}
	void setScale(float x, float y, float z){
		scale[0] = x;
		scale[1] = y;
		scale[2] = z;
	}

	const DirectX::XMVECTOR* getPosition(){
		return &mMatrix.r[3];
	}
protected:
	DirectX::XMMATRIX mMatrix;
	float scale[4];
private:

};