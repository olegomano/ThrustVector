#include "Collision.h"

void Collision::resolveCollision(double dt){
	if (!o1->checkCollision(o2)) return; //collision resolved itself
	double dtColl = getCollisionTime(o1, o2);
	if (dtColl < 0 && dtColl > -dt * 2){
		//ballModel(dtColl);
		energyLossModel(dtColl,dt);
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


	Vec3 velProjectionVec = (obj1Pos - obj2Pos);
	Vec3 velProjectionUnit = tUnitVec(&velProjectionVec);

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

void Collision::energyLossModel(double dtColl, double dt){
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

	double randXmod = (std::rand() % 340) / 1000;
	double randYmod = (std::rand() % 340) / 1000;

	Vec3 velProjectionVec = (obj1Pos - obj2Pos);
	Vec3 velProjectionUnit = tUnitVec(&velProjectionVec);
	
	int neg = rand() % 1;
	if (neg){
		velProjectionUnit.x += randXmod;
	}
	else{
		velProjectionUnit.x -= randXmod;
	}
	neg = rand() % 1;
	if (neg){
		velProjectionUnit.y += randYmod;
	}
	else{
		velProjectionUnit.y -= randYmod;
	}
	velProjectionUnit = tUnitVec(&velProjectionUnit);

	Vec3 velSaveComponentObj1;
	Vec3 velSaveComponentObj2;

	double obj1VelProj = dotProduct(&velProjectionUnit, &obj1Vel);
	double obj2VelProj = dotProduct(&velProjectionUnit, &obj2Vel);

	velSaveComponentObj1 = (obj1Vel - velProjectionUnit*obj1VelProj);
	velSaveComponentObj2 = (obj2Vel - velProjectionUnit*obj2VelProj);

	double obj1Elasticity = o1->getElasticity() + (std::rand() % 130) / 1000;
	double obj2Elasticity = o2->getElasticity() + (std::rand() % 130) / 1000;

	double obj1NewVelComp = (obj1Elasticity*o2->getMass()*(obj2VelProj - obj1VelProj) + o1->getMass()*obj1VelProj + o2->getMass()*obj2VelProj) / (o1->getMass() + o2->getMass());
	double obj2NewVelComp = (obj2Elasticity*o2->getMass()*(obj1VelProj - obj2VelProj) + o1->getMass()*obj1VelProj + o2->getMass()*obj2VelProj) / (o1->getMass() + o2->getMass());

	Vec3 obj1NewVel = (velSaveComponentObj1 + velProjectionUnit*obj1NewVelComp);
	Vec3 obj2NewVel = (velSaveComponentObj2 + velProjectionUnit*obj2NewVelComp);

	Vec3 obj1Force = ((obj1NewVel - obj1Vel) / (dtColl));
	Vec3 obj2Force = ((obj2NewVel - obj2Vel) / (dtColl));

	double tangentVelObj1Mag = vecMag(&velSaveComponentObj1);
	double tangentVelObj2Mag = vecMag(&velSaveComponentObj2);

	double obj1F = ((tangentVelObj1Mag - tangentVelObj1Mag*(o1->getElasticity()))/(dtColl))*o1->getMass()*.1;
	double obj2F = ((tangentVelObj2Mag - tangentVelObj2Mag*(o2->getElasticity()))/ (dtColl))*o2->getMass()*.1;



	o1->applyTangentalForce(obj2F);
	o2->applyTangentalForce(obj1F);
	o1->setVelocity(obj1NewVel);
	o2->setVelocity(obj2NewVel);
	o1->calculateVelocity(dtColl);
	o2->calculateVelocity(dtColl);
	o1->move((dtColl));
	o2->move((dtColl));
	o1->resetFrame();
	o2->resetFrame();
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