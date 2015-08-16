#include "Collision.h"

void Collision::resolveCollision(double dt){
	if (!o1->checkCollision(o2)) return; //collision resolved itself
	double dtColl = getCollisionTime(o1, o2);
	if (dtColl < 0 && dtColl > -dt ){
		Vec3 mOrigin1 = *const_cast<Vec3*>(o1->getPosition());
		Vec3 oOrigin1 = *const_cast<Vec3*>(o2->getPosition());
		double distanceStart = getDistance(&mOrigin1, &oOrigin1);


		Vec3 o1CurVel = o1->getVelocity();
		Vec3 o2CurVel = o2->getVelocity();

		o1->setVelocity(obj1Vel); 
		o2->setVelocity(obj2Vel);
		
		o1->move(dtColl);
		o2->move(dtColl);

		
		o1->setVelocity(o1CurVel);
		o2->setVelocity(o2CurVel);


		Vec3 newVelocity = (obj1Vel*o1->getMass() + obj2Vel*o2->getMass()) / ((o1->getMass() + o2->getMass())*1.157);
		Vec3 o1F = ((newVelocity - obj1Vel) / (dt))* o1->getMass();
		Vec3 o2F = ((newVelocity - obj2Vel) / (dt)) * o2->getMass();
		
		o1->setVelocity(newVelocity);
		o1->applyForce(&o1F);
		o2->setVelocity(newVelocity);
		o2->applyForce(&o2F);

		o1->calculateVelocity(dt);
		o2->calculateVelocity(dt);

		o1->resetFrame();
		o2->resetFrame();

		o1->onCollisionResolved(o2);
		o2->onCollisionResolved(o1);

	
		
	}
	else{
		/*
		Vec3 mOrigin = *const_cast<Vec3*>(o1->getPosition());
		Vec3 oOrigin = *const_cast<Vec3*>(o2->getPosition());
		double distance = getDistance(&mOrigin, &oOrigin);
		double idealDistance = o1->getHitboxRad() + o2->getHitboxRad();
		Vec3 o1SVel = obj1Vel;
		Vec3 o2SVel = obj2Vel;
		Vec3 curr1Vel = o1->getVelocity();
		Vec3 curr2Vel = o2->getVelocity();
		int a = 10;
		*/

		/*
		double v1Mag = vecMagSqr(&obj1Vel);
		double v2Mag = vecMagSqr(&obj2Vel);
		Vec3 dir = *const_cast<Vec3*>(o1->getPosition()) - *const_cast<Vec3*>(o2->getPosition());
		dir = tUnitVec(&dir);
		Vec3 v1;
		Vec3 v2;
		Vec3 vel;
		if (v1Mag > v2Mag){
			o1->setVelocity(obj1Vel*.95);
			o2->setVelocity(obj1Vel*.15);
		}
		else{
			o1->setVelocity(obj2Vel*.75);
		}
		//o1->move(-dtColl/15);
		//o2->move(-dtColl/15);
		*/


		/*
		Vec3 nVel;
		Vec3 f1 = tUnitVec(&o1->getVelocity())*-.000035;
		Vec3 f2 = tUnitVec(&o2->getVelocity())*-.000035;
		o1->setVelocity(nVel);
		o2->setVelocity(nVel);
		o1->applyForce(&f1);
		o2->applyForce(&f2);
		o1->calculateVelocity(dt);
		o1->move(dt);
		o1->resetFrame();
		o2->calculateVelocity(dt);
		o2->move(dt);
		o2->resetFrame();
		*/

	}
};


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
	double rRes = res.x < 0 ? res.x : res.y;
	return rRes;
}