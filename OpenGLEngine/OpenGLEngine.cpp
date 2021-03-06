// OpenGLEngine.cpp : Defines the entry point for the console application.
//
#define GLFW_INCLUDE_GLU
//#pragma comment(lib, "glfw3.lib")
#include "stdafx.h"

#include <iostream>
#include <windows.h>
#include "glut.h"
#include <Python.h>
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

vector2 mouse(0,0);
vector2 screen(800,600);
//vector2 screen(1500,800);
MapCollection maps;
Player player;

void drawGui();
void drawMenu();
void mouseClick(int button,int state,int x,int y);
void drawBoxedMenu(int rows,std::string text);

using namespace std;

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
	//glfwDisable(GLFW_MOUSE_CURSOR);
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
		case ' ':
			if (player.jump == 2 && maps.curr == maps.GAME)
			{
				player.jump = 1;
				player.jumpYPos = player.position.y;
				//position.y++;
			}
			else if (maps.curr == maps.MENU)
			{
				maps.curr = maps.GAME;
			}
			break;
		case 27:
			//glutDestroyWindow(Win.id);
			//exit(0);
			maps.paused = !maps.paused;
			if (!maps.paused)
				glutSetCursor(GLUT_CURSOR_NONE);
			else
				glutSetCursor(GLUT_CURSOR_CROSSHAIR);
			break;
		case '/':
			player.position.x = 0;
			player.position.z = 0;
			break;
		case '5':
			player.health--;
			break;
		case '8': case 'w': case 'W':
			player.speed.x = 0;
			player.speed.z = 0;
			break;
		case '2': case 's': case 'S':
			player.speed.x = 0;
			player.speed.z = 0;
			break;
		case 'q': case 'Q':
			maps.fireBullet(player.position,0,player.lx,player.ly,player.lz);
			break;
		case 'r': case 'R':
			maps.reload();
			break;
		case 'p': case 'P':
			glutFullScreen();
			break;
		case 'b': case 'B':
			std::cout << "Breaking the game :D";
			break;
		case 'f': case 'F':
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
void keyCommands()
{
	typedef std::map<unsigned char, bool>::iterator it_type;
	for(it_type iterator = maps.keyState.begin(); iterator != maps.keyState.end(); iterator++) 
	{
		if (iterator->second)
		{
			switch(iterator->first)
			{
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

			case 'q': case 'Q':
				//bulletpair.fireBullet();
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
	if (!maps.paused)
	{
	static bool warped = false;
	bool capture = false;	
    if( warped )
    {
        warped = false;
        return;
    }

	mouse.x = x;
	mouse.y = y;
	if (x != screen.x || y != screen.y)
		capture = true;
	if (capture)
	{
		warped = true;
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
		if (y < screen.y/2 && player.vertAngle < 0.8)
		{
			player.vertAngle += 0.05f;
			player.ly = sin(player.vertAngle);
			glutWarpPointer(screen.x/2,screen.y/2);
		}
		else if (y > screen.y/2 && player.vertAngle > -0.8)
		{
			player.vertAngle -= 0.05f;
			//if (player.vertAngle > 360)
				//player.vertAngle = 360;
			player.ly = sin(player.vertAngle);
			glutWarpPointer(screen.x/2,screen.y/2);
		}
	}
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
	if (!maps.paused)
	{
		bool fall = maps.update(player.speed,player.position,player.size,player.jump,player.invTimer,player.health,player.lightInf);
	player.update(fall);
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	///<summary>Draw commands </summary>
	//glutStrokeCharacter(GLUT_STROKE_ROMAN,player.position.y);

	switch(maps.curr)
	{
	case maps.GAME:
		
		gluLookAt(player.position.x,player.position.y + 1.0f,player.position.z, player.position.x + player.lx, player.position.y + 1.0f + player.ly,player.position.z + player.lz, 0.0f, 1.0f,0.0f);

		player.draw();
		maps.draw();
	
		drawGui();

		break;
	case maps.MENU:
		drawMenu();
		break;
	case maps.EXIT:
		break;
	case maps.SPLASH:
		break;
	case maps.OPTIONS:
		break;
	}
	glFlush();
	glutSwapBuffers();
	
	///<summary>Update commands </summary>
	update();
	keyCommands();
}

static float CallPythonFunc()
{
	PyObject *pName, *pModule, *pDict, *pFunc, *pValue, *pArgs;
	float ret;

	Py_Initialize();

	pName = PyBytes_FromString("testPython");

	pModule = PyImport_ImportModule("testPython");

	pDict = PyModule_GetDict(pModule);

	pFunc = PyDict_GetItemString(pDict, "wander");


	if (PyCallable_Check(pFunc))
	{
		pArgs = PyTuple_New(2 /*number of arguments*/);

		// Argument 1
		pValue = PyFloat_FromDouble((double)5);
		PyTuple_SetItem(pArgs, 0, pValue);

		// Argument 2
		pValue = PyFloat_FromDouble((double)6);
		PyTuple_SetItem(pArgs, 1, pValue);

		pValue = PyObject_CallObject(pFunc, pArgs);

		ret = (float)PyFloat_AsDouble(pValue);

	}
	Py_Finalize();

	return ret;
}



int main(int argc, char** argv)
{
	//if (!glfwInit())
		//exit(EXIT_FAILURE);


	try // always check for Python_exceptions
	{

		// Create an instance of the interpreter.
		//PyObject py(argc, argv);
		Py_SetProgramName((wchar_t*)argv[0]);
		Py_Initialize();
		std::cout << CallPythonFunc();
		Py_Finalize();

	}
	catch (exception ex)
	{
		std::cout << ex.what();
	}




	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen.x,screen.y);
	glutInitWindowPosition(50,50);
	glutCreateWindow("Darths 3d engine, Fo Shizzle");

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);
	glutSpecialFunc(keyboard_s);
	glutPassiveMotionFunc(mouseMotion);
	glutIgnoreKeyRepeat(GL_TRUE);
	glutMouseFunc(mouseClick);
	init();
	glutMainLoop();

    return(1);
}

void mouseClick(int button,int state,int x,int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !maps.paused) {
		maps.fireBullet(player.position,player.angle,player.lx,player.ly,player.lz);
    }
	else if (maps.paused && y > (screen.y / 2) - (screen.y / 5) && y < (screen.y/2) + (screen.y/5) && x > screen.x/4 && x < (screen.x/2) + (screen.x/4))
		exit(0);
}

void drawGui()
{
	

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, screen.x, screen.y, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);
	
	/////////////////////Health bar///////////
	if (maps.whatBullet < 10)
	for(int i = maps.whatBullet; i != 10;i++)
	{
	glBegin(GL_QUADS);
		float color = 1-(i*0.1f)+0.1f;
		glColor3f(0.0f, color, 0.0);

		glVertex2f(((screen.x/40)*(i+1)),10);
		glVertex2f(((screen.x/40)*(i+1)),20);
		glVertex2f(((screen.x/40)*(i+1)) + 10,20);
		glVertex2f(((screen.x/40)*(i+1)) + 10,10);


	glEnd();
	}
	else
	{
		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0);

		glVertex2f((screen.x/40),10);
		glVertex2f((screen.x/40),20);
		glVertex2f((screen.x/4),20);
		glVertex2f((screen.x/4),10);
	}
	/////////////////////Health bar///////////
	if (player.health > 0)
	{
	glBegin(GL_QUADS);
		if (player.invTimer == 0)
			glColor3f(1.0f, 0.0f, 0.0);	
		else
			glColor3f(1.0f, 0.0f, 1.0);	
		
		glVertex2f((screen.x/2 - (screen.x/6)) - 2.6*(100 - player.health),screen.y - (screen.y/35)); 
		glVertex2f((screen.x/2 - (screen.x/6)) - 2.6*(100 - player.health),screen.y - (screen.y/15));
		glVertex2f((screen.x/35), screen.y - (screen.y/15));
		glVertex2f((screen.x/35),screen.y-(screen.y/35));



	glEnd();
	}
	/////////////////////Mana/energy bar///////////
	if (player.mana > 0)
	{
	glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 1.0);
		
		glVertex2f((screen.x/2 + (screen.x/6)) + 2.6*(100 - player.mana),screen.y - (screen.y/35)); 
		glVertex2f((screen.x/2 + (screen.x/6)) + 2.6*(100 - player.mana),screen.y - (screen.y/15));
		glVertex2f((screen.x- (screen.x/35)), screen.y - (screen.y/15));
		glVertex2f((screen.x -(screen.x/35)),screen.y-(screen.y/35));

	glEnd();
	}
	//////////////////////Top////////////////
	glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 0.0);

		glVertex2f(0.0, 0.0);
		glVertex2f(screen.x/2.5,0.0);
		glVertex2f(screen.x/2.5,0.0);

		//glVertex2f(300, 200);
		glVertex2f(screen.x/2.5-(screen.x/6), screen.y/15);
		glVertex2f(0.0, screen.y/20);

	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 0.0);

		glVertex2f(screen.x, 0.0);
		glVertex2f(screen.x - screen.x/2.5,0.0);
		glVertex2f(screen.x - screen.x/2.5,0.0);

		//glVertex2f(300, 200);
		glVertex2f(screen.x - screen.x/2.5+(screen.x/6), screen.y/15);
		glVertex2f(screen.x, screen.y/20);

	glEnd();
	/////////////////////////Bottom///////////////////
	glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 0.0);

		glVertex2f(0, screen.y);
		glVertex2f(screen.x/2,screen.y);
		glVertex2f(screen.x/2,screen.y);

		//glVertex2f(300, 200);
		glVertex2f(screen.x/2-(screen.x/6), screen.y - screen.y/10);
		glVertex2f(0, screen.y - screen.y/10);

	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 0.0);

		glVertex2f(screen.x, screen.y);
		glVertex2f(screen.x/2,screen.y);
		glVertex2f(screen.x/2,screen.y);

		//glVertex2f(300, 200);
		glVertex2f(screen.x/2+(screen.x/6), screen.y - screen.y/10);
		glVertex2f(screen.x, screen.y - screen.y/10);

	glEnd();
	if (!maps.paused)
	{
	/////////////////////Pointer//////////////
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.8,0.8,0.8);
		
		glVertex2f(screen.x/2,screen.y/2);//a
		glColor3f(0,0,0);
		glVertex2f(((screen.x/2)+screen.x/94),screen.y/2);//b
		glVertex2f((screen.x/2),(screen.y/2)-screen.y/94);//c
		glVertex2f(((screen.x/2)-screen.x/94),screen.y/2);//d
		glVertex2f((screen.x/2) - screen.x/132,(screen.y/2)+screen.y/94);//e
		glVertex2f((screen.x/2) + screen.x/132,(screen.y/2)+screen.y/94);//f
		glVertex2f(((screen.x/2)+screen.x/94),screen.y/2);//g
		
		glVertex2f(screen.x/2,screen.y/2);//h

		
	glEnd();
	
	}
	else
	{
		drawBoxedMenu(4, "Line1|Line2|Line3|Line4|");
		/*glBegin(GL_QUADS);
		
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2f(screen.x/4,(screen.y/2) + (screen.y/5));
			glColor3f(0.2f, 0.0f, 0.0f);
			glVertex2f(screen.x/4,(screen.y/2) - (screen.y/5));
			glColor3f(0.0f, 0.2f, 0.0f);
			glVertex2f((screen.x/2) + (screen.x/4),(screen.y/2) - (screen.y/5));
			glColor3f(0.0f, 0.0f, 0.2f);
			glVertex2f((screen.x/2) + (screen.x/4),(screen.y/2) + (screen.y/5));

		glEnd();*/
	}


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void drawMenu()
{
	
	gluLookAt(0.0, 30.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, screen.x, screen.y, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);
	
	/////////////////////Health bar///////////
	//GLFONT font;
    //glFontCreate(&font, "TrojanFont.glf", 0);
	//glFontBegin(&font);
	//glScalef(8.0, 8.0, 8.0);
	//glRotatef(180,0,0,0);x
	glTranslatef(30, 30, 0);
	//glFontTextOut("Test", 5, 5, 0);
	//glFontEnd();
	//glFlush();
	//glBegin(GL_QUADS);
	char text[13] = "Menu Shiz";
	for (int i = 0; i != 9; i++)
	{
		glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef((screen.x/8) +(screen.x/18) *i, screen.x/6, 0);
		glRotatef(180, 1.0, 0.0, 0.0);
		glScalef(0.2,0.2,0.2);
		glutStrokeCharacter(GLUT_STROKE_ROMAN,text[i]);
		glPopMatrix();
	}	
	text[0] = 'S';
	text[1] = 'p';
	text[2] = 'a';
	text[3] = 'c';
	text[4] = 'e';
	text[5] = ' ';
	text[6] = 'T';
	text[7] = 'o';
	text[8] = ' ';
	text[9] = 'P';
	text[10] = 'l';
	text[11] = 'a';
	text[12] = 'y';
	for (int i = 0; i != 13; i++)
	{
		glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef((screen.x/8) +(screen.x/18) *i, screen.x/2, 0);
		glRotatef(180, 1.0, 0.0, 0.0);
		glScalef(0.1,0.1,0.1);
		glutStrokeCharacter(GLUT_STROKE_ROMAN,text[i]);
		glPopMatrix();
	}	

	//glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

//Use the mouse click function along side this
void drawBoxedMenu(int rows,std::string text)
{
	std::string daText[6];
	std::string delimiter = "|";
	size_t pos = 0;
	std::string token;// = text.substr(0, text.find(delimiter));

	int order = 0;
	while ((pos = text.find(delimiter)) != std::string::npos) {
		token = text.substr(0, pos);
		std::cout << token << std::endl;
		daText[order] = token;
		text.erase(0, pos + delimiter.length());
		order++;
	}
	//float boxY = (

	if (rows > 6)
		rows = 6;


	
	for (int i = 0;order > i;i++)
	{
		//for(int ii = daText[order].size(); ii > 0; ii--)
		{
		int ii = 0;
		for (auto c = daText[i].begin(); c != daText[i].end(); ++c)
		{ 
			ii++;
			glPushMatrix();
			glColor3f(1,0,0);
			glTranslatef((screen.x/4) + (ii*(screen.x/40)), ((screen.y/8.5)*i) + (screen.y/6), 0);
			glRotatef(180, 1.0, 0.0, 0.0);
			glScalef(0.2,0.2,0.2);
			glutStrokeCharacter(GLUT_STROKE_ROMAN,*c);
			glPopMatrix();
		}
		}
	}

	for (int i = 0; i < rows; i++)
	{
		glBegin(GL_QUADS);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2f(screen.x/4,((screen.y/8.5)*i) + (screen.y/4));
			glVertex2f(screen.x/4,((screen.y/8.5)*i) + (screen.y/6));
			glVertex2f(screen.x/2 + screen.x/4,((screen.y/8.5)*i) + (screen.y/6));
			glVertex2f(screen.x/2 + screen.x/4,((screen.y/8.5)*i) + (screen.y/4));
		glEnd();
		//for (int
		//glutStrokeCharacter(GLUT_STROKE_ROMAN,text[0]);
	}
	
	glBegin(GL_QUADS);

		glColor3f(0,0,0);

		glVertex2f((screen.x/4.5) - 20,((screen.y/8.5)*rows) + (screen.y/4) - 20);
		
		glVertex2f(screen.x/4.5,(screen.y/6) - 20);
		
		glVertex2f(((screen.x/2) + (screen.x/3.5)) - 20,(screen.y/6) - 20);
		
		glVertex2f((screen.x/2) + (screen.x/3.5),((screen.y/8.5)*rows) + (screen.y/4) - 20);


	glEnd();

}