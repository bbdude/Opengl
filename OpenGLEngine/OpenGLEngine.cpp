// OpenGLEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windows.h>
#include "glut.h"
#include <stdio.h>
#include <gl/GL.h>
#include <gl\GLU.h>
#include "SOIL.h"
#include <map>
#include "VectorLib.h"
#include <math.h>
#include "BasicShape.h"
#include "Tree.h"
#include "MapCollection.h"
#include "Cube.h"
#include "Player.h"

#define MAX_VERTICES 2000 
#define MAX_POLYGONS 2000

vector2 mouse(0,0);
vector2 screen(800,600);
MapCollection maps;
Player player;

void init(void)
{
	glClearColor(0.0,0.0,0.2,0.0);
	glShadeModel(GL_SMOOTH);
	glViewport(0,0,screen.x,screen.y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)screen.x/(GLfloat)screen.y,1.0f,1000.0f);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glutSetCursor(GLUT_CURSOR_NONE);
	maps.init(1,1,3,1);
}

void resize(int width, int height)
{
	screen.x = width;
	screen.y = height;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,screen.x,screen.y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)screen.x/(GLfloat)screen.y,1.0f,1000.0f);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	maps.keyState[key] = true;
}
void keyboard_up(unsigned char key, int x, int y)
{
	maps.keyState[key] = false;
	switch(key)
	{
		case '8': case 'w': case 'W':
			player.speed.x = 0;
			player.speed.z = 0;
			break;
		case '2': case 's': case 'S':
			player.speed.x = 0;
			player.speed.z = 0;
			break;
		case 'q': case 'Q':
			maps.fireBullet(player.position,0,player.lx,player.lz);
			break;
		case 'r': case 'R':
			maps.reload();
			break;
		case 'p': case 'P':
			glutFullScreen();
			break;
	}
}
void keyCommands()
{
	typedef std::map<unsigned char, bool>::iterator it_type;
	for(it_type iterator = maps.keyState.begin(); iterator != maps.keyState.end(); iterator++) 
	{
		if (iterator->second)
		{
			switch(iterator->first)
			{
			case 27:
				//glutDestroyWindow(Win.id);
				exit(0);
				break;
			case '4': case 'a': case 'A':
				//angle -= 0.005f;
				//lx = sin(angle);
				//lz = -cos(angle);
				//position.x -= lx * 0.1f;
				//position.z += lz * 0.1f;
				break;
			case '8': case 'w': case 'W':
				//position.x += lx * 0.1f;
				//position.z += lz * 0.1f;
				player.speed.x = player.lx * 0.1f;
				player.speed.z = player.lz * 0.1f;
				break;
			case '2': case 's': case 'S':
				//position.x -= lx * 0.1f;
				//position.z -= lz * 0.1f;
				player.speed.x = -(player.lx * 0.1f);
				player.speed.z = -(player.lz * 0.1f);
				break;
			case '6': case 'd': case 'D':
				//position.x += lx * 0.1f;
				//angle += 0.005f;
				//lx = sin(angle);
				//lz = -cos(angle);
				break;

			case ' ':
		
				if (player.jump == 2)
				{
					player.jump = 1;
					player.jumpYPos = player.position.y;
					//position.y++;
				}
				break;
			case 'q': case 'Q':
				//bulletpair.fireBullet();
				break;
			case 'r': case 'R':
				if(player.filling == 0)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					player.filling = 1;
				}
				else
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					player.filling = 0;
				}
				break;
			}
		}
	}
}
void keyboard_s(int key, int x,int y)
{
	switch(key)
	{
	case GLUT_ACTIVE_SHIFT:
		player.position.y--;
		break;
	}
}

void mouseMotion(int x, int y)
{
	//int button,int state, 
	//if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
		//bulletpair.fireBullet();
	//if (x >= screen.x/2 + 60 || x <= screen.x/2 - 60)
	//{
	/*
	if (x > mouse.x)
	{
		player.angle -= 0.05f;
		player.lx = sin(player.angle);
		player.lz = -cos(player.angle);
	}
	else if (x < mouse.x)
	{
		player.angle += 0.05f;
		player.lx = sin(player.angle);
		player.lz = -cos(player.angle);
	}
	if (y > mouse.y)
	{
		player.vertAngle += 0.05f;
		if (player.vertAngle < 360)
			player.vertAngle = 360;
		player.ly = sin(player.vertAngle);
	}
	else if (y < mouse.y)
	{
		player.vertAngle -= 0.05f;
		if (player.vertAngle < 0)
			player.vertAngle = 0;
		player.ly = sin(player.vertAngle);
	}
	*/
	//if (mouse.x < 10)
	//	glutWarpPointer(50,mouse.y);
	//else if (mouse.x > screen.x - 10)
	//	glutWarpPointer(screen.x - 50,mouse.y);
	//if (mouse.y < 10)
	//	glutWarpPointer(mouse.x,50);
	//else if (mouse.y > screen.y - 10)
	//	glutWarpPointer(mouse.x, screen.y - 50);
	mouse.x = x;
	mouse.y = y;
	if (x > screen.x/2)
	{
		player.angle -= 0.05f;
		player.lx = sin(player.angle);
		player.lz = -cos(player.angle);
		glutWarpPointer(screen.x/2,screen.y/2);
	}
	else if (x < screen.x/2)
	{
		player.angle += 0.05f;
		//if (player.vertAngle < 0)
			//player.vertAngle = 0;
		player.lx = sin(player.angle);
		player.lz = -cos(player.angle);
		glutWarpPointer(screen.x/2,screen.y/2);
	}
	if (y < screen.y/2)
	{
		player.vertAngle += 0.05f;
		player.ly = sin(player.vertAngle);
		glutWarpPointer(screen.x/2,screen.y/2);
	}
	else if (y > screen.y/2)
	{
		player.vertAngle -= 0.05f;
		//if (player.vertAngle > 360)
			//player.vertAngle = 360;
		player.ly = sin(player.vertAngle);
		glutWarpPointer(screen.x/2,screen.y/2);
	}
	//glutWarpPointer(screen.x/2,screen.y/2);
}

int detectXZCollision(float x,float y,float xx, float yy, vector2 size)
{
	int x_offset, y_offset;
	int left,right,top,bottom;

	left = xx;
	right = left + size.x;
	top = yy;
	bottom = top + size.y;

	if (x < left) return 0;
	if (x > right) return 0;

	if (y < top) return 0;
	if (y > bottom) return 0;

	x_offset = abs(x- xx);
	y_offset = abs((y - yy) * size.x);

	/*
	float left1,left2;
	float right1,right1;
	float top1,top2;
	float bottom1,bottom2;

	left1 = x;
	left2 = xx;
	right1 = x + size.x;
	right2 = x + sizeTwo.x;
	top1 = y;
	top2 = yy;
	bottom1 = y + size.y;
	bottom2 = yy + sizeTwo.y;

	if (bottom1 < top2) return (0);
	if (top1 > bottom2) return (0);
	if (right1 < left 2)return (0);
	if (left1 > right2) return (0);

	return (1);
	*/
	return 1;
}

void update()
{
	//bool falling = maps.update(player.speed,player.position,player.size,player.jump) ;
	bool fall = maps.update(player.speed,player.position,player.size,player.jump);
	player.update(fall);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(player.position.x,player.position.y + 1.0f,player.position.z, player.position.x + player.lx, player.position.y + 1.0f + player.ly,player.position.z + player.lz, 0.0f, 1.0f,0.0f);

	///<summary>Draw commands </summary>
	glutStrokeCharacter(GLUT_STROKE_ROMAN,player.position.y);
	maps.draw();

	glFlush();
	glutSwapBuffers();
	
	///<summary>Update commands </summary>
	update();
	keyCommands();
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen.x,screen.y);
	glutInitWindowPosition(50,50);
	glutCreateWindow("Darths 3d engine");

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);
	glutSpecialFunc(keyboard_s);
	glutPassiveMotionFunc(mouseMotion);
	glutIgnoreKeyRepeat(GL_TRUE);
	init();
	glutMainLoop();

    return(1);
}



/*
void drawTraingle(int x, int y)
{
	y = screen.y - y;
	//x is bottom mid point on x, y is bottoms mid point on y, z is top points 
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,screen.x,0,screen.y, -5,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_TRIANGLES);

	glColor3f(0.5,0.5,0.5);
	glVertex2f( x - 10,y + 10);
	glVertex2f( x + 10,y + 10);
	glVertex2f(x, y - 10);

	glEnd();
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glDepthMask(0);
}
*/