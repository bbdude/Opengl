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
	speed.x = 0.05f;
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