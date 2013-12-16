#pragma once
#include "cube.h"
#include "VectorLib.h"
#include "Collision.h"

class Bullet :
	public Cube
{
public:
	Bullet(void);
	~Bullet(void);

	void operator << (Bullet change);
	void updateSpeed();
	vector3 speed;
	bool killOff;
	//float angle;
};

