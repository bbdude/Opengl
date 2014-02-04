#include "StdAfx.h"
#include "Tree.h"


Tree::Tree(void)
{
	position.x = 0;
	position.y = 0;
	position.z = 0;
	
	top.init(0,0,0);
	middle.init(0,0,0);
	base.init(0,0,0);
}
Tree::Tree(int x, int y, int z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	
	top.init(x,y + 5,z);
	middle.init(x,y - 5,z);
	base.init(x,y - 10,z);
}
Tree::Tree(vector3 change)
{
	position << change;
	change.y += 5;
	top.init(change);
	change.y -= 10;
	middle.init(change);
	change.y -= 5;
	base.init(change);
}
Tree::~Tree(void)
{
}
///*
void Tree::draw(void)
{
	top.draw(1,1,1);
	middle.draw(0.3f,0.4f,0.1f);
	base.draw(0.52f,0.37f,0.26f);
	/*
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);

	glTranslatef(position.x,position.y + 5,position.z);
	glRotatef(-90.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(base, height, 10, 2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2f, 0.4f,0.1f);
	glTranslatef(position.x, position.y -5,position.z);
	glRotatef(-90.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(base, height + 10, 10, 2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.52f,0.37f,0.26f);
	glTranslatef(position.x, position.y -10,position.z);
	glRotatef(-90.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(base - 5, height + 10, 10, 2);
	glPopMatrix();
	*/
}
void Tree::init(int x,int y,int z, float height,float base)
{
	position.x = x;
	position.y = y;
	position.z = z;
	
	top.init(x,y + 5,z,base,height);
	middle.init(x,y - 5,z,base,height + 10);
	this->base.init(x,y - 10,z,base - 5,height + 10);
}

//*/