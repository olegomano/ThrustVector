#include "Ship.h"


Ship::Ship()
{
}

void Ship::draw(float dt){
	PlaneDrawable::draw(dt);
}

const Vec3* Ship::getPosition(){
	return( Vec3*)(&mMatrix.r[3]);
}

Ship::~Ship()
{
}
