#pragma once
#include "Structs.h"
#include "PhysObj.h"
class Camera : public PhysObj
{
public:
	Camera();
	Camera(Vec3* pos);
	void applyTransform(DirectX::XMMATRIX* trans);
	void setFollow(DirectX::XMVECTOR* follow);
	void fillOutCb(cbCamera* out);
	void updateFrame();
	float getFocusDistance();
	~Camera();
private:
	DirectX::XMVECTOR* followVector = nullptr;
	DirectX::XMMATRIX  mMatrix;
	float perspectiveData[4];
};

