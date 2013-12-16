#pragma once
#include "enemy.h"
#include "Cube.h"
class Goomba :
	public Enemy
{
public:
	Goomba(void);
	~Goomba(void);

	vector3 startingPoint;
	vector3 distanceMoveable;
	bool rebound;
	bool killOff;
	Cube cube;

	void update();
	void initlize(vector3 starting,vector3 speed, vector3 distance);
	void draw(void);
};

