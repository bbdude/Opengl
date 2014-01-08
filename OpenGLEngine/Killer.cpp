#include "StdAfx.h"
#include "Killer.h"


Killer::Killer(void)
{
}


Killer::~Killer(void)
{
}

void Killer::update()
{
	//cone.up

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

	//speed.x = 0.05f;
	cone.position += speed;
}
void Killer::initlize(vector3 starting,vector3 speed, vector3 distance)
{
	position = starting;
	this->speed = speed;
	distanceMoveable = distance;
	vector2 newSize(0,0);
	vector3 color(1,0,0);
	bullet.fill(position,newSize,color,0);
}
void Killer::draw(void)
{
	cone.draw(0.53, 0.12, 0.47);
	bullet.draw();
}

void Killer::fill(vector3 position, vector2 size, vector3 color, float angle)
{
	this->position = position;
	this->size.fill(size.x,size.y,size.x);
	size.x = (size.x + size.y)/2;
	cone.fill(position,size,color);
}
void Killer::fill(vector3 position, vector2 size, float angle)
{
	
	this->position = position;
	this->size.fill(size.x,size.y,size.x);
	size.x = (size.x + size.y)/2;
	cone.fill(position,size);
}