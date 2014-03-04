#pragma once
#include "enemy.h"
#include "Cube.h"
class Goomba :
	public Enemy
{
public:
	Goomba(void);
	~Goomba(void);

	vector3 startingPoint;
	vector3 distanceMoveable;
	bool rebound;
	bool killOff;
	Cube cube;
	GLuint	texture[10];
	float curTex;
	float light;
	void update(float lighInf,vector3 playerPos);
	void initlize(vector3 starting,vector3 speed, vector3 distance);
	void draw(void);
	int LoadGLTextures();
	int LoadGLTextures(int limit);
};

