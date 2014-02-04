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
	LoadGLTextures("Rec/test.bmp");
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
	//cube.draw();
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);	
	glDepthFunc(GL_LEQUAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glColor4f(0.5f,0,0.5f,0.5f);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	/*glBegin(GL_TRIANGLES);
	for (int l_index = 0; l_index < 12; l_index++)
	{
		//glRotatef(angle,1,0,0);
		//glColor3f(cube.color.x,cube.color.y,cube.color.z);
		if (cube.angle != 0)
			glRotatef(-cube.angle * 100,0.0, 0.0, 1.0);
		glVertex3f( cube.vertex[ cube.polygon[l_index].a ].x, cube.vertex[ cube.polygon[l_index].a ].y, cube.vertex[ cube.polygon[l_index].a ].z);
		glVertex3f( cube.vertex[ cube.polygon[l_index].b ].x, cube.vertex[ cube.polygon[l_index].b ].y, cube.vertex[ cube.polygon[l_index].b ].z);
		glVertex3f( cube.vertex[ cube.polygon[l_index].c ].x, cube.vertex[ cube.polygon[l_index].c ].y, cube.vertex[ cube.polygon[l_index].c ].z);
	}
	glEnd();*/
	
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);	
	glDepthFunc(GL_LEQUAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
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
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
int Goomba::LoadGLTextures(char * loc)									
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