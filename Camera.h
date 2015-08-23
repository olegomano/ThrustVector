#pragma once
#include "Structs.h"
#include "TransformBase.h"
#include "PhysObjBase.h"
class Camera : public TransformBase
{
public:
	Camera();
	Camera(Vec3* pos);
	void fillOutCb(cbCamera* out);
	float getNear(){
		return perspectiveData[0];
	}
	float getFar(){
		return perspectiveData[1];
	}
	float getFocusDistance(){
		return perspectiveData[2];
	}
	void setFollowObj(PhysObjBase* t){
		followObj = t;
	}
	void updateCameraPosition(double dt);
	~Camera();
private:
	float perspectiveData[4]; //near far focus
	PhysObjBase* followObj = nullptr;
};

