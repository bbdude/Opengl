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
	polygon[11].set(2, 1, 0);
	filename = "cube.png";
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
	polygon[11].set(2, 1, 0);
	filename = "cube.png";

}
void Cube::init()
{
	curTex = 0;

	LoadGLTextures(filename);
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

	light = 0.5f;
}
void Cube::update(float lighInf, vector3 playerPos)
{
	update();
	float distance = sqrt((playerPos.x - position.x)*(playerPos.x - position.x) + (playerPos.y - position.y)*(playerPos.y - position.y) + (playerPos.z - position.z)*(playerPos.z - position.z));
	light = distance * 0.01f;
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
void Cube::drawTex(void)
{
	//draw();/*
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//if(texture[(int)curTex] != 0)
	glBindTexture(GL_TEXTURE_2D, texture);
	//glColor4f(0.1f + light,0.1f + light,0.1f + light,0.1f + light);
	//glColor4f(0.1f - light,0.1f - light,0.1f - light,0.1f - light);

	glColor4f(1 - light, 1 - light, 1 - light, 1 - light);
	//glColor4f(0.5f,0.5f,0.5f,0.5f);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_TRIANGLES);
	for (int l_index = 0; l_index < 12; l_index++)
	{
		//glRotatef(angle, 1, 0, 0);
		//glColor3f(color.x,color.y,color.z);
		//if (angle != 0)
		//	glRotatef(-angle * 100, 0.0, 0.0, 1.0);
		glTexCoord2f(0, 0); glVertex3f(vertex[polygon[l_index].a].x, vertex[polygon[l_index].a].y, vertex[polygon[l_index].a].z);
		glTexCoord2f(1, 0); glVertex3f(vertex[polygon[l_index].b].x, vertex[polygon[l_index].b].y, vertex[polygon[l_index].b].z);
		glTexCoord2f(0, 1); glVertex3f(vertex[polygon[l_index].c].x, vertex[polygon[l_index].c].y, vertex[polygon[l_index].c].z);

	}
	glEnd();
	//if (texture[(int)curTex] != 0 && curTex < 5)
	//	curTex += 0.01f;
	//else
	//	curTex = 0;
	glDepthFunc(GL_LESS);
	glDisable(GL_TEXTURE_2D);//*/
	glPopMatrix();
}
void Cube::drawTexN(void)
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glBindTexture(GL_TEXTURE_2D, texture);

	glColor4f(1 - light, 1 - light, 1 - light, 1 - light);
	glBegin(GL_TRIANGLES);
	for (int l_index = 0; l_index < 12; l_index++)
	{
		glTexCoord2f(0, 0); glVertex3f(vertex[polygon[l_index].a].x, vertex[polygon[l_index].a].y, vertex[polygon[l_index].a].z);
		glTexCoord2f(1, 0); glVertex3f(vertex[polygon[l_index].b].x, vertex[polygon[l_index].b].y, vertex[polygon[l_index].b].z);
		glTexCoord2f(0, 1); glVertex3f(vertex[polygon[l_index].c].x, vertex[polygon[l_index].c].y, vertex[polygon[l_index].c].z);

	}
	glEnd();
	glDepthFunc(GL_LESS);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
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

int Cube::LoadGLTextures(std::string file)
{
	//std::string file = "cube.png";
	texture = SOIL_load_OGL_texture
		(
		(char*)file.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if (texture == 0)
		return false;


	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	return true;										// Return Success
}
/*
int Cube::LoadGLTextures(int limit)
{
	/* load an image file directly as a new OpenGL texture 
	for (int i = 0; i <= limit; i++)
	{

		//char *theString = "test";
		std::stringstream ss;
		ss << filename << i << ".png";
		char * S = new char[ss.str().length() + 1];
		std::strcpy(S, ss.str().c_str());
		//char text[10] = { 't'
		//char * point = (char*)("test" + limit);
		texture[i] = SOIL_load_OGL_texture
			(
			S,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y
			);
		int * height = (int*)20, *width = (int*)20, *channel = (int*)0;
		SOIL_load_image(S,width,height,channel,0);

		if (texture[i] == 0)
			return false;


		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	return true;										// Return Success
}*/