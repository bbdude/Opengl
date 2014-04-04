#pragma once
#include "basicshape.h"
#include "VectorLib.h"

class Enemy :
	public BasicShape
{
public:
	Enemy(void);
	~Enemy(void);

	//void update(vector3 playerPos);
	//void initlize();

	//G is goomba like movement
	//j is jumber
	//c is chaser
	//a is assin
	//v is velcro
	//x is xenogeny
	//e is ellifant
	//f is flyer
	//y is y
	//i is intelligent
	//h is healer
	//o is OP
	//r is rabid
	//u is uneven
	//s is speedy
	//t is terrible
	//k is killer
	//l is lame
	//b is bane
	//m is money(fake)
	//n is nope(chucktesta)
	//p is party
	//q is quarrel
	//d is demon
	//z is zealous
	//w is walker
	//
	char type;
	float wander();
	vector2 seek(float x, float z, float xt, float zt,float speed);
	float seekX();
	float seekZ();
};

