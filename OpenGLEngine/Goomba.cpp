#include "StdAfx.h"
#include "Goomba.h"


Goomba::Goomba(void)
{
}


Goomba::~Goomba(void)
{
}



void Goomba::update()
{
	if (distanceMoveable.x + startingPoint.x <= position.x && speed.x > 0)
	{
		speed.x *= -1;
	}
	else if (startingPoint.x - distanceMoveable.x  >= position.x && speed.x < 0)
	{
		speed.x *= -1;
	}
	
	if (distanceMoveable.z + startingPoint.z <= position.z && speed.z > 0)
	{
		speed.z *= -1;
	}
	else if (startingPoint.z - distanceMoveable.z  >= position.z && speed.z < 0)
	{
		speed.z *= -1;
	}

	position += speed;
	cube.position = position;
	cube.update();
}
void Goomba::initlize(vector3 starting,vector3 speed, vector3 distance)
{
	type = 'g';
	cube.color.x = 0;
	cube.color.z = 0;
	cube.color.y = 1;
	cube.size.x = 5;
	cube.size.y = 5;

	rebound = false;
	startingPoint = starting;
	this->speed = speed;
	distanceMoveable = distance;
	position = starting;
	cube.position = position;
	killOff = false;
}

void Goomba::draw(void)
{
	cube.draw();
}