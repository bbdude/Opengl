#include "StdAfx.h"
#include "Cone.h"


Cone::Cone(void)
{
	position = position.empty();
}
Cone::Cone(int x, int y, int z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}
Cone::Cone(vector3 change)
{
	position = change;
}
Cone::Cone(int x, int y, int z,float base,int height)
{
	position.x = x;
	position.y = y;
	position.z = z;
	this->base = base;
	this->height = height;
}
Cone::Cone(vector3 change,float base,int height)
{
	position = change;
	this->base = base;
	this->height = height;
}


void Cone::init(int x, int y, int z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}
void Cone::init(vector3 change)
{
	position = change;
}
void Cone::init(int x, int y, int z,float base,int height)
{
	position.x = x;
	position.y = y;
	position.z = z;
	this->base = base;
	this->height = height;
}
void Cone::init(vector3 change,float base,int height)
{
	position = change;
	this->base = base;
	this->height = height;
}

Cone::~Cone(void)
{
}

void Cone::draw(void)
{
	glPushMatrix();
	glColor3f(0.2f, 0.4f,0.1f);
	glTranslatef(position.x, position.y,position.z);
	glRotatef(-90.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(base, height, 10, 2);
	glPopMatrix();
}
void Cone::draw(GLfloat r,GLfloat g,GLfloat b)
{
	glPushMatrix();
	glColor3f(r,g,b);
	glTranslatef(position.x, position.y,position.z);
	glRotatef(-90.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(base, height, 10, 2);
	glPopMatrix();
}

void Cone::fill(vector3 position, vector2 size, vector3 color)
{
	this->position = position;
	height = size.y;
	base = size.x;
	this->color = color;
}
void Cone::fill(vector3 position, vector2 size)
{
	this->position = position;
	height = size.y;
	base = size.x;
}

void Cone::update(void)
{
	position += speed;
}