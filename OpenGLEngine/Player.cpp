#include "StdAfx.h"
#include "Player.h"
#include <iostream>


Player::Player(void)
{
	size.fill(10,10,10);
	jump = 0;
	angle = 0.0f;
	vertAngle = 0.0f;
	jumpYPos = -15;
	lx = 0.0f;
	lz = -1.0f;
	ly = 0.0f;
	position.fill(-40,2,5);
	speed.fill(0,0,0);
	health = 100;
	mana = 100;
	invTimer = 0;
	//vector3 positionArm(position.x,position.y,position.z);
	vector3 positionArm(0,0,0);
	vector2 positionSize(2,5);
	positionArm.x -= 5;
	positionArm.z -= 5;
	lArm.fill(positionArm,positionSize,45.0f);
	positionArm.x += 10;
	positionArm.z += 10;
	rArm.fill(positionArm,positionSize,0.0f);
	armAngle = 0;
}


Player::~Player(void)
{
}

void Player::update(bool fall)
{
	//lArm.position.x = lx * 0.5f;
	//lArm.position.z = lz * 0.5f;
	//armAngle += 0.25f;
	if (armAngle >= 360)
		armAngle = 0;
	//rArm.position.x = -1 *(lx * 0.5f);
	//rArm.position.z = -1 *(lz * 0.5f);
	//lArm.angle += 0.25f;
	//lArm.position = position;
	//lArm.position.x -= size.x*2;

	//rArm.position = position;
	//rArm.position.x += size.x*2;

	lArm.update();
	rArm.update();

	if (position.y <= jumpYPos+30 && jump == 1)
		speed.y = 0.2f;
	else if (jump == 1)
		jump = 0;
	else if (position.y >= 0 && !fall)
	{
		speed.y = -0.2f;
	}
	else
	{
		jump = 2;
		speed.y = 0;
	}
	position.y += speed.y;
	position.x += speed.x;
	position.z += speed.z;
}

void Player::draw()
{
	//vector2 aAngle(lx,lz);
	//vector2 zero(0,0);
	//armAngle += 0.25;// =  aAngle.dotProduct(zero);

	glPushMatrix();
	//glTranslatef(position.x + 1.5,position.y,position.z - 0.5);
	glTranslatef(position.x,position.y,position.z);
	
	//glRotatef(armAngle,0,1,0);
	glRotatef(armAngle,0,1,0);

	//glTranslatef(-position.x - 1.5,-position.y,-position.z - 0.5);
	glTranslatef(-position.x,-position.y,-position.z);

	lArm.draw(0,0,0,0,0,0,0,0,0);
	glPopMatrix();
	


	glPushMatrix();
	glTranslatef(position.x,position.y,position.z);

	//glRotatef(armAngle-180,0,1,0);
	glRotatef(armAngle-180,0,1,0);

	//glTranslatef(position.x - 1.5,position.y,position.z - 0.5);

	//glTranslatef(-position.x - 1.5,-position.y,-position.z - 0.5);
	glTranslatef(-position.x,-position.y,-position.z);
	glTranslatef(position.x,position.y,position.z);

	rArm.draw(1,1,1,1,1,1,1,1,1);
	glPopMatrix();
}