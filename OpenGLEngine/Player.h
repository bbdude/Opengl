#pragma once
#include "VectorLib.h"
#include "Cube.h"

class Player
{
public:
	Player(void);
	~Player(void);

	void update(bool fall);
	void draw();

	vector3 position;
	vector3 speed;
	vector3 size;
	int filling;
	int jump;
	int health;
	int mana;
	float invTimer;
	float angle;
	float vertAngle;
	float jumpYPos;
	float lx;
	float lz;
	float ly;
	
	Cube lArm;
	Cube rArm;
	float armAngle;
	//vector3 position(-40,2,5);
	//vector3 speed(0,0,0);

};

