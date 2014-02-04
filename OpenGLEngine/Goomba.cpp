#include "StdAfx.h"
#include "Goomba.h"


Goomba::Goomba(void)
{
}


Goomba::~Goomba(void)
{
}



void Goomba::update(float lighInf,vector3 playerPos)
{
	float distance = sqrt( (playerPos.x-position.x)*(playerPos.x-position.x) + (playerPos.y-position.y)*(playerPos.y-position.y) + (playerPos.z-position.z)*(playerPos.z-position.z));
	//distance /= ;
	light = distance * 0.01f;
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
	LoadGLTextures(5);
	type = 'g';
	cube.color.x = 0;
	cube.color.z = 0;
	cube.color.y = 1;
	cube.size.x = 5;
	cube.size.y = 5;
	light = 0;
	rebound = false;
	startingPoint = starting;
	this->speed = speed;
	distanceMoveable = distance;
	position = starting;
	cube.position = position;
	killOff = false;
	curTex = 0;
}

/*void Goomba::draw(void)
{
	cube.draw();
}*/
void Goomba::draw(void)
{
	//cube.draw();
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);	
	glDepthFunc(GL_LEQUAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//if(texture[(int)curTex] != 0)
		glBindTexture(GL_TEXTURE_2D, texture[(int)curTex]);
		//glColor4f(0.1f + light,0.1f + light,0.1f + light,0.1f + light);
		//glColor4f(0.1f - light,0.1f - light,0.1f - light,0.1f - light);
		glColor4f(1 - light,1 - light,1 - light,1 - light);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	bool half = false;
	glBegin(GL_TRIANGLES);
	for (int l_index = 0; l_index < 12; l_index++)
	{
		half = !half;
		glRotatef(cube.angle,1,0,0);
		//glColor3f(cube.color.x,cube.color.y,cube.color.z);
		if (cube.angle != 0)
			glRotatef(-cube.angle * 100,0.0, 0.0, 1.0);
		if (!half)
		{
		glTexCoord2f(0,0);glVertex3f( cube.vertex[ cube.polygon[l_index].a ].x, cube.vertex[ cube.polygon[l_index].a ].y, cube.vertex[ cube.polygon[l_index].a ].z);
		//glTexCoord3f( cube.polygon[l_index].a, cube.polygon[l_index].a, cube.polygon[l_index].a);glVertex3f( cube.vertex[ cube.polygon[l_index].a ].x, cube.vertex[ cube.polygon[l_index].a ].y, cube.vertex[ cube.polygon[l_index].a ].z);
		glTexCoord2f(1,0);glVertex3f( cube.vertex[ cube.polygon[l_index].b ].x, cube.vertex[ cube.polygon[l_index].b ].y, cube.vertex[ cube.polygon[l_index].b ].z);
		//glTexCoord3f( cube.polygon[l_index].b, cube.polygon[l_index].b, cube.polygon[l_index].b);glVertex3f( cube.vertex[ cube.polygon[l_index].b ].x, cube.vertex[ cube.polygon[l_index].b ].y, cube.vertex[ cube.polygon[l_index].b ].z);
		glTexCoord2f(1,1);glVertex3f( cube.vertex[ cube.polygon[l_index].c ].x, cube.vertex[ cube.polygon[l_index].c ].y, cube.vertex[ cube.polygon[l_index].c ].z);
		//glTexCoord3f( cube.polygon[l_index].c, cube.polygon[l_index].c, cube.polygon[l_index].c);glVertex3f( cube.vertex[ cube.polygon[l_index].c ].x, cube.vertex[ cube.polygon[l_index].c ].y, cube.vertex[ cube.polygon[l_index].c ].z);
		}
		else
		{
		glTexCoord2f(0,0);glVertex3f( cube.vertex[ cube.polygon[l_index].a ].x, cube.vertex[ cube.polygon[l_index].a ].y, cube.vertex[ cube.polygon[l_index].a ].z);
		//glTexCoord3f( cube.polygon[l_index].a, cube.polygon[l_index].a, cube.polygon[l_index].a);glVertex3f( cube.vertex[ cube.polygon[l_index].a ].x, cube.vertex[ cube.polygon[l_index].a ].y, cube.vertex[ cube.polygon[l_index].a ].z);
		glTexCoord2f(1,0);glVertex3f( cube.vertex[ cube.polygon[l_index].b ].x, cube.vertex[ cube.polygon[l_index].b ].y, cube.vertex[ cube.polygon[l_index].b ].z);
		//glTexCoord3f( cube.polygon[l_index].b, cube.polygon[l_index].b, cube.polygon[l_index].b);glVertex3f( cube.vertex[ cube.polygon[l_index].b ].x, cube.vertex[ cube.polygon[l_index].b ].y, cube.vertex[ cube.polygon[l_index].b ].z);
		glTexCoord2f(1,1);glVertex3f( cube.vertex[ cube.polygon[l_index].c ].x, cube.vertex[ cube.polygon[l_index].c ].y, cube.vertex[ cube.polygon[l_index].c ].z);
		//glTexCoord3f( cube.polygon[l_index].c, cube.polygon[l_index].c, cube.polygon[l_index].c);glVertex3f( cube.vertex[ cube.polygon[l_index].c ].x, cube.vertex[ cube.polygon[l_index].c ].y, cube.vertex[ cube.polygon[l_index].c ].z);
		}
	}
	glEnd();/*

	
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);	
	glDepthFunc(GL_LEQUAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	if(texture[(int)curTex] != 0)
		glBindTexture(GL_TEXTURE_2D, texture[(int)curTex]);
	glColor4f(0.5f,0,0.5f,0.5f);
	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();*/
	if(texture[(int)curTex] != 0 && curTex < 5)
		curTex+= 0.01f;
	else
		curTex = 0;
	glDisable(GL_TEXTURE_2D);
}

int Goomba::LoadGLTextures()									
{
	/* load an image file directly as a new OpenGL texture */
	texture[0] = SOIL_load_OGL_texture
		(
		"test.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if(texture[0] == 0)
		return false;


	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	return true;										// Return Success
}
int Goomba::LoadGLTextures(int limit)									
{
	/* load an image file directly as a new OpenGL texture */
	for (int i = 0; i <= limit; i++)
	{

		char *theString = "test";
		std::stringstream ss;
		ss << theString << i << ".png";
		char * S = new char[ss.str().length() + 1];
		std::strcpy(S,ss.str().c_str());
		//char text[10] = { 't'
	//char * point = (char*)("test" + limit);
	texture[i] = SOIL_load_OGL_texture
		(
		S,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if(texture[i] == 0)
		return false;
	

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}

	return true;										// Return Success
}