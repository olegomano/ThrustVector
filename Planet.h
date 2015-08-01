#pragma once
#include "ForceGenerator.h"
#include "Drawable.h"
#include "Plane.h"

class Planet : public ForceGenerator, Drawable
{
public:
	Planet();
	Planet(float rad, float m){
		radius = rad;
		mass = m;
	}
	~Planet();
	void create(ID3D11Device* pd3dDevice, ID3D11DeviceContext*  context, Shader* shader){
		Drawable::create(pd3dDevice, context, shader);
		mPlane.allocBuffers(pd3dDevice);
		mPlane.setShader(*shader);
	}
	Vec3* getPosition();
	void  setPosition(Vec3* newPos){
		for (int i = 0; i < 3; i++){
			((float*)(&mPosition))[i] = ((float*)(newPos))[i];
			mPlane.getModelMat()->r[3].m128_f32[i] = ((float*)(newPos))[i];
		}
	};
	void applyForceOn(PhysObj* obj);
	void draw(float dt);
private:
	float radius = 5;
	float mass = 100;
	Vec3 mGenForce;
	Vec3 mPosition;
	Plane mPlane;
};

