#include "StdAfx.h"
#include "Collision.h"


Collision::Collision(void)
{
}

//Collision::Collision(vector3 & speed, vector3 & position,vector3 & vecCenter, float & radius)
//{
//	this->speed = speed;
//	this->position = position;
//	this->vecCenter = vecCenter;
//	this->radius = radius;
//}
Collision::Collision(vector3 speed, vector3 position,vector3 vecCenter, float radius)
{
	this->speed = speed;
	this->position = position;
	this->vecCenter = vecCenter;
	this->radius = radius;
}


Collision::~Collision(void)
{
}

bool Collision::mSphereCollision(void)
{
	vector3 vecv1 = position - vecCenter;

	float fb = vecv1.dot(speed);

	float fc = vecv1.dot(vecv1) - (radius * radius);

	if (fc > 0.0f && fb > 0.0f)
		return false;

	float fDisc = fb*fb-fc;

	if (fDisc < 0.0f)
		return false;

	return true;
}

bool Collision::SpheretSphere(const  Collision sph2)
{
	vector3 vecDist(vecCenter - sph2.vecCenter);
	float fDistSq = vecDist.dot(vecDist);
	float fRad = radius + sph2.radius;
	fRad *= fRad;

	if (fDistSq <= fRad)
		return true;
	return false;
}


bool Collision::checkSquareToSquareX(const Collision sph2)
{
	int dis;
	dis = abs( sqrt( std::sqrt(position.x - sph2.position.x - speed.x) + std::sqrt(position.z - sph2.position.z))); //include cmath
    dis -= this->radius;
	dis -= sph2.radius;

    if (dis<=0) //collision
    return true;

    //no collision
    return false;

}bool Collision::checkSquareToSquareZ(const Collision sph2)
{
	int dis;

	dis = abs( sqrt( std::sqrt(position.x - sph2.position.x) + std::sqrt(position.z - sph2.position.z - speed.z))); //include cmath
    dis -= this->radius;
	dis -= sph2.radius;

    if (dis<=0) //collision
    return true;

    //no collision
    return false;

}