#pragma once
#include "VectorLib.h"
#include <cmath>

class Collision
{
public:
	Collision(void);
	//Collision(vector3 & speed, vector3 & position,vector3 & vecCenter, float & radius);
	Collision(vector3 speed, vector3 position,vector3 vecCenter, float radius);
	~Collision(void);

	//Moving Sphere Collision
	bool mSphereCollision(void);
	//Sphere to Sphere collsision
	bool SpheretSphere(const  Collision sph2);
	bool checkSquareToSquareX(const Collision sph2);
	bool checkSquareToSquareZ(const Collision sph2);

	vector3 speed;
	vector3 position;

	vector3 vecCenter;
	float radius;
	
};

