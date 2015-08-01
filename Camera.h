#pragma once
#include "Structs.h"
#include "TransformBase.h"

class Camera : public TransformBase
{
public:
	Camera();
	Camera(Vec3* pos);
	void fillOutCb(cbCamera* out);
	float getFocusDistance();
	~Camera();
private:
	float perspectiveData[4];
};

