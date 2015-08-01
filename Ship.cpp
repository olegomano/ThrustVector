#include "Ship.h"


Ship::Ship()
{
}

void Ship::draw(float dt){
	calculateDisplace(dt);
	for (int i = 0; i < 3; i++){
		mPlane.getModelMat()->r[3].m128_f32[i] = ((float*)(&position))[i];
	}
	mPlane.draw(context);
}

Ship::~Ship()
{
}
