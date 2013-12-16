#pragma once
#include "VectorLib.h"

class Player
{
public:
	Player(void);
	~Player(void);

	void update(bool fall);

	vector3 position;
	vector3 speed;
	vector3 size;
	int filling;
	int jump;
	int health;
	float invTimer;
	float angle;
	float vertAngle;
	float jumpYPos;
	float lx;
	float lz;
	float ly;
	//vector3 position(-40,2,5);
	//vector3 speed(0,0,0);

};

