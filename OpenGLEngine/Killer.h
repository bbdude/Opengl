#pragma once
#include "enemy.h"
#include "Bullet.h"
#include "Cone.h"

class Killer :
	public Enemy
{
public:
	Killer(void);
	~Killer(void);

	vector3 startingPoint;
	vector3 distanceMoveable;
	bool killOff;
	Cone cone;
	Bullet bullet;

	void update();
	void initlize(vector3 starting,vector3 speed, vector3 distance);
	void fill(vector3 position, vector2 size, vector3 color, float angle);
	void fill(vector3 position, vector2 size, float angle);
	void draw(void);
};

