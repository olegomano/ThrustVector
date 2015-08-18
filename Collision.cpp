#include "Collision.h"

void Collision::resolveCollision(double dt){
	if (!o1->checkCollision(o2)) return; //collision resolved itself
	double dtColl = getCollisionTime(o1, o2);
	if (dtColl < 0 && dtColl > -dt * 2){
		energyLossModel(dtColl);
	}
	else{
		int error = 1;

	}
};

void Collision::ballModel(double dtColl){	
	Vec3 mOrigin = *const_cast<Vec3*>(o1->getPosition());
	Vec3 oOrigin = *const_cast<Vec3*>(o2->getPosition());
	double startDistance = getDistance(&mOrigin, &oOrigin);

	Vec3 o1CurVel = o1->getVelocity();
	Vec3 o2CurVel = o2->getVelocity();

	double angle = dotProduct(&tUnitVec(&o1CurVel), &tUnitVec(&o2CurVel));

	o1->setVelocity(obj1Vel);
	o2->setVelocity(obj2Vel);

	o1->move(dtColl);
	o2->move(dtColl);

	mOrigin = *const_cast<Vec3*>(o1->getPosition());
	oOrigin = *const_cast<Vec3*>(o2->getPosition());
	double currDistance = getDistance(&mOrigin, &oOrigin);
	double neededDistance = o1->getHitboxRad() + o2->getHitboxRad();

	o1->setVelocity(o1CurVel);
	o2->setVelocity(o2CurVel);
	
	Vec3 newVelocity = (obj1Vel*o1->getMass() + obj2Vel*o2->getMass()) / ((o1->getMass() + o2->getMass())*3.6);

	double randXmod = (std::rand() % 200) / 100;
	double randYmod = (std::rand() % 200) / 100;
	Vec3 modPosO1 = obj1Pos;
	Vec3 modPosO2 = obj2Pos;

	int negative = std::rand() % 1;

	if (negative){
		modPosO1.x -= randXmod;
	}
	else{
		modPosO1.x += randXmod;
	}
	negative = std::rand() % 1;
	if (negative){
		modPosO1.y -= randYmod;
	}
	else{
		modPosO1.y += randYmod;
	}

	randXmod = (std::rand() % 200) / 100;
	randYmod = (std::rand() % 200) / 100;
	negative = std::rand() % 1;

	if (negative){
		modPosO2.x -= randXmod;
	}
	else{
		modPosO2.x += randXmod;
	}

	negative = std::rand() % 1;
	if (negative){
		modPosO2.y -= randYmod;
	}
	else{
		modPosO2.y += randYmod;
	}

	double randElasticityMod = ((std::rand() % 10) / 100) + .85;

	Vec3 velProjectionVec = (modPosO1 - modPosO2);
	Vec3 velProjectionUnit = tUnitVec(&velProjectionVec)*(randElasticityMod);

	Vec3 collisionNormal(-velProjectionVec.y, velProjectionVec.x, velProjectionVec.z);

	Vec3 velSaveComponentObj1;
	Vec3 velSaveComponentObj2;

	double obj1VelProj = dotProduct(&velProjectionUnit, &obj1Vel);
	double obj2VelProj = dotProduct(&velProjectionUnit, &obj2Vel);

	velSaveComponentObj1 = (obj1Vel - velProjectionUnit*obj1VelProj);
	velSaveComponentObj2 = (obj2Vel - velProjectionUnit*obj2VelProj);
	
	double obj1NewVelComp = ((obj1VelProj*(o1->getMass() - o2->getMass()) + 2 * o2->getMass() * obj2VelProj) / (o1->getMass() + o2->getMass()));
	double obj2NewVelComp = ((obj2VelProj*(o2->getMass() - o1->getMass()) + 2 * o1->getMass() * obj1VelProj) / (o1->getMass() + o2->getMass()));
	
	Vec3 obj1NewVel = (velSaveComponentObj1 + velProjectionUnit*obj1NewVelComp);
	Vec3 obj2NewVel = (velSaveComponentObj2 + velProjectionUnit*obj2NewVelComp);

	o1->setVelocity(obj1NewVel);
	o2->setVelocity(obj2NewVel);
	o1->onCollisionResolved(o2);
	o2->onCollisionResolved(o1);
}

void Collision::energyLossModel(double dtColl){
	Vec3 mOrigin = *const_cast<Vec3*>(o1->getPosition());
	Vec3 oOrigin = *const_cast<Vec3*>(o2->getPosition());
	double startDistance = getDistance(&mOrigin, &oOrigin);

	Vec3 o1CurVel = o1->getVelocity();
	Vec3 o2CurVel = o2->getVelocity();

	double angle = dotProduct(&tUnitVec(&o1CurVel), &tUnitVec(&o2CurVel));

	o1->setVelocity(obj1Vel);
	o2->setVelocity(obj2Vel);

	o1->move(dtColl);
	o2->move(dtColl);

	mOrigin = *const_cast<Vec3*>(o1->getPosition());
	oOrigin = *const_cast<Vec3*>(o2->getPosition());
	double currDistance = getDistance(&mOrigin, &oOrigin);
	double neededDistance = o1->getHitboxRad() + o2->getHitboxRad();

	o1->setVelocity(o1CurVel);
	o2->setVelocity(o2CurVel);

	double randXmod = (std::rand() % 200) / 100;
	double randYmod = (std::rand() % 200) / 100;
	Vec3 modPosO1 = obj1Pos;
	Vec3 modPosO2 = obj2Pos;

	int negative = std::rand() % 1;

	if (negative){
		modPosO1.x -= randXmod;
	}
	else{
		modPosO1.x += randXmod;
	}
	negative = std::rand() % 1;
	if (negative){
		modPosO1.y -= randYmod;
	}
	else{
		modPosO1.y += randYmod;
	}

	randXmod = (std::rand() % 200) / 100;
	randYmod = (std::rand() % 200) / 100;
	negative = std::rand() % 1;

	if (negative){
		modPosO2.x -= randXmod;
	}
	else{
		modPosO2.x += randXmod;
	}

	negative = std::rand() % 1;
	if (negative){
		modPosO2.y -= randYmod;
	}
	else{
		modPosO2.y += randYmod;
	}

	double randElasticityMod = ((std::rand() % 10) / 100) + .85;

	Vec3 velProjectionVec = (modPosO1 - modPosO2);
	Vec3 velProjectionUnit = tUnitVec(&velProjectionVec)*(randElasticityMod);

	Vec3 collisionNormal(-velProjectionVec.y, velProjectionVec.x, velProjectionVec.z);

	Vec3 velSaveComponentObj1;
	Vec3 velSaveComponentObj2;

	double obj1VelProj = dotProduct(&velProjectionUnit, &obj1Vel);
	double obj2VelProj = dotProduct(&velProjectionUnit, &obj2Vel);

	velSaveComponentObj1 = (obj1Vel - velProjectionUnit*obj1VelProj);
	velSaveComponentObj2 = (obj2Vel - velProjectionUnit*obj2VelProj);

	double obj1NewVelComp = ( ( ( obj1VelProj*(o1->getMass()) - o2->getMass() ))*o1->getElasticity() + 2 * o2->getMass() * obj2VelProj) / (o1->getMass() + o2->getMass());
	double obj2NewVelComp = ( ( ( obj2VelProj*(o2->getMass())-  o1->getMass() ))*o2->getElasticity() + 2 * o1->getMass() * obj1VelProj) / (o1->getMass() + o2->getMass());

	Vec3 obj1NewVel = (velSaveComponentObj1 + velProjectionUnit*obj1NewVelComp);
	Vec3 obj2NewVel = (velSaveComponentObj2 + velProjectionUnit*obj2NewVelComp);

	o1->setVelocity(obj1NewVel);
	o2->setVelocity(obj2NewVel);
	o1->onCollisionResolved(o2);
	o2->onCollisionResolved(o1);
}


double Collision::getCollisionTime(PhysObjBase* me, PhysObjBase* other){
	Vec3 mOrigin = obj1Pos;
	Vec3 oOrigin = obj2Pos;
	Vec3 dOrigin = mOrigin - oOrigin;
	Vec3 dVel = obj1Vel - obj2Vel;
	Vec3 dDVDOM = dOrigin * dVel;

	Vec3 dVelSQ = dVel*dVel;
	Vec3 dOrigSq = dOrigin*dOrigin;

	double sumDO = dOrigin.x + dOrigin.y + dOrigin.z;
	double sumDV = dVel.x + dVel.y + dVel.z;

	double sumDOSq = dOrigSq.x + dOrigSq.y + dOrigSq.z;
	double sumDVSq = dVelSQ.x + dVelSQ.y + dVelSQ.z;

	double sumDVDO = dDVDOM.x + dDVDOM.y + dDVDOM.z;

	double idealDistance = me->getHitboxRad() + other->getHitboxRad();
	double distance = vecMagSqr(&dOrigin);
	idealDistance *= idealDistance;

	if (sumDV == 0){
		Vec3 nVel;
		me->setVelocity(nVel);
		other->setVelocity(nVel);
		return 0;
	}

	Point res = solveQuadratic(sumDVSq, sumDVDO * 2, sumDOSq - idealDistance);
	double rRes = res.x < res.y ? res.x : res.y;
	return rRes;
}