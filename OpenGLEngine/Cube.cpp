#include "StdAfx.h"
#include "Cube.h"


Cube::Cube(void)
{
	for (int i = 0; i < 7; i ++)
	{
		vertex[i].x = 0;
		vertex[i].y = 0;
		vertex[i].z = 0;
	}
	
	polygon[0].set(0,1,4);
	polygon[1].set(1,5,4);
	polygon[2].set(1,2,5);
	polygon[3].set(2,6,5);
	polygon[4].set(2,3,6);
	polygon[5].set(3,7,6);
	polygon[6].set(3,0,7);
	polygon[7].set(0,4,7);
	polygon[8].set(4,5,7);
	polygon[9].set(5,6,7);
	polygon[10].set(3,2,0);
	polygon[11].set(2,1,0);
}

Cube::Cube(float x, float y,float z,float width,float height)
{
	position.x = x;
	position.y = y;
	position.z = z;

	this->size.x = width;
	this->size.y = height;
	for (int i = 0; i < 8; i ++)
	{
		vertex[i].x = 0;
		vertex[i].y = 0;
		vertex[i].z = 0;
	}
	
	polygon[0].set(0,1,4);
	polygon[1].set(1,5,4);
	polygon[2].set(1,2,5);
	polygon[3].set(2,6,5);
	polygon[4].set(2,3,6);
	polygon[5].set(3,7,6);
	polygon[6].set(3,0,7);
	polygon[7].set(0,4,7);
	polygon[8].set(4,5,7);
	polygon[9].set(5,6,7);
	polygon[10].set(3,2,0);
	polygon[11].set(2,1,0);
}

Cube::~Cube(void)
{
}

void Cube::update()
{

	vector3 pos(position);

	vertex[7].x = pos.x;
	vertex[4].x = pos.x;
	vertex[3].x = pos.x;
	vertex[0].x = pos.x;

	vertex[6].x = pos.x + size.x;
	vertex[5].x = pos.x + size.x;
	vertex[2].x = pos.x + size.x;
	vertex[1].x = pos.x + size.x;
	
	vertex[7].y = pos.y;
	vertex[6].y = pos.y;
	vertex[5].y = pos.y;
	vertex[4].y = pos.y;
	
	vertex[3].y = pos.y - size.y;
	vertex[2].y = pos.y - size.y;
	vertex[1].y = pos.y - size.y;
	vertex[0].y = pos.y - size.y;
	
	vertex[5].z = pos.z;
	vertex[4].z = pos.z;
	vertex[1].z = pos.z;
	vertex[0].z = pos.z;

	vertex[7].z = pos.z - size.x;
	vertex[6].z = pos.z - size.x;
	vertex[3].z = pos.z - size.x;
	vertex[2].z = pos.z - size.x;
}

void Cube::draw(void)
{
	glBegin(GL_TRIANGLES);
	for (int l_index = 0; l_index < 12; l_index++)
	{
		//glRotatef(angle,1,0,0);
		glColor3f(color.x,color.y,color.z);
		if (angle != 0)
			glRotatef(-angle * 100,0.0, 0.0, 1.0);
		glVertex3f( vertex[ polygon[l_index].a ].x, vertex[ polygon[l_index].a ].y, vertex[ polygon[l_index].a ].z);
		glVertex3f( vertex[ polygon[l_index].b ].x, vertex[ polygon[l_index].b ].y, vertex[ polygon[l_index].b ].z);
		glVertex3f( vertex[ polygon[l_index].c ].x, vertex[ polygon[l_index].c ].y, vertex[ polygon[l_index].c ].z);
	}
	glEnd();
}
void Cube::draw(GLfloat r, GLfloat g, GLfloat b)
{
	glBegin(GL_TRIANGLES);
	for (int l_index = 0; l_index < 12; l_index++)
	{
		if (angle != 0)
			glRotatef(-90.0f,0.0, 1.0, 1.0);
		glColor3f(r,g,b);
		glVertex3f( vertex[ polygon[l_index].a ].x, vertex[ polygon[l_index].a ].y, vertex[ polygon[l_index].a ].z);
		glVertex3f( vertex[ polygon[l_index].b ].x, vertex[ polygon[l_index].b ].y, vertex[ polygon[l_index].b ].z);
		glVertex3f( vertex[ polygon[l_index].c ].x, vertex[ polygon[l_index].c ].y, vertex[ polygon[l_index].c ].z);
	}
	glEnd();
}
void Cube::draw(GLfloat r, GLfloat g, GLfloat b,GLfloat rr, GLfloat gg, GLfloat bb,GLfloat rrr, GLfloat ggg, GLfloat bbb)
{
	glBegin(GL_TRIANGLES);
	glPushMatrix();
	for (int l_index = 0; l_index < 12; l_index++)
	{
		//if (angle != 0)
		//	glRotatef(-90.0f,0.0, 1.0, 1.0);
		glColor3f(r,g,b);
	//glRotatef(45,0.0, 1.0, 1.0);
		glVertex3f( vertex[ polygon[l_index].a ].x, vertex[ polygon[l_index].a ].y, vertex[ polygon[l_index].a ].z);
		glColor3f(rr,gg,bb);
	//glRotatef(45,0.0, 1.0, 1.0);
		glVertex3f( vertex[ polygon[l_index].b ].x, vertex[ polygon[l_index].b ].y, vertex[ polygon[l_index].b ].z);
		glColor3f(rrr,ggg,bbb);
	//glRotatef(45,0.0, 1.0, 1.0);
		glVertex3f( vertex[ polygon[l_index].c ].x, vertex[ polygon[l_index].c ].y, vertex[ polygon[l_index].c ].z);
	}
	glRotatef(45,0.0, 1.0, 1.0);
	glPopMatrix();
	glEnd();
}

void Cube::setColor(GLfloat r,GLfloat g,GLfloat b)
{
	color.x = r;
	color.y = g;
	color.z = b;
}

void Cube::fill(vector3 position, vector2 size, vector3 color, float angle)
{
	this->position = position;
	this->size = size;
	this->color = color;
	this->angle = angle;
}
void Cube::fill(vector3 position, vector2 size, float angle)
{
	this->position = position;
	this->size = size;
	this->angle = angle;
	this->color.fill(0,0,0);
}