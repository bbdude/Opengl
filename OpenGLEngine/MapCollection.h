#pragma once
#include <map>
#include <iostream>
#include <string>
#include "BasicShape.h"
#include "Tree.h"
#include "VectorLib.h"
#include "Cube.h"
#include "Bullet.h"
#include "Goomba.h"
#include "Killer.h"

class MapCollection
{
public:
	MapCollection(void);
	~MapCollection(void);

	void init(int trees,int cubes, int goombas,int killers);
	void draw(void);
	void fireBullet(vector3 & playerPos,float angle, float lx,float ly, float lz);
	void reload();
	bool update(vector3 & playerSpeed,vector3 & playerPos, vector3 & playerSize, int & jump, float & invtimer,float & playerHealth,float & playerInf);
	bool check_collision(float x,float y,float xx, float yy, vector3 size, vector3 sizeTwo);
	bool testRadialCollision(vector3 & speed,vector3 & position,float & radius,vector3 & speedTwo,vector3 & positionTwo,float & radiusTwo,vector3 & sizeTwo);
	bool check_diff(int n1, int n2, int fat);
	bool CheckBoxCollision( vector3 PointA, vector3 PointB, vector3 SizeA, vector3 SizeB);

	std::map<int, Tree  > trees;
	std::map<int, Bullet> bullets;
	std::map<int, Goomba> goombas;
	std::map<int, Killer> killers;
	std::map<std::string, Cube> cubes;
	std::map<unsigned char, bool> keyState;

	int whatBullet;
	bool reloadGun;
	bool paused;

	enum STATE {SPLASH,MENU,GAME,EXIT,OPTIONS};
	STATE curr;

	Bullet masterBullet;
};

