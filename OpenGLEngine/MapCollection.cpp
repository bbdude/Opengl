#include "StdAfx.h"
#include "MapCollection.h"
#include "Collision.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

MapCollection::MapCollection(void)
{
}


MapCollection::~MapCollection(void)
{
}

void MapCollection::init(int trees,int cubes,int goombas,int killers)
{
	curr = MENU;
	vector2 size(-1000,1);
	vector3 position(500,-10,-500);
	vector3 goombaDist(5,0,5);
	vector3 color(0.4,0.3,0);

	this->cubes["Floor"];
	this->cubes["Floor"].fill(position,size,color,0);

	size.x = -10;
	size.y = 10;
	position.fill(5,3,5);
	this->cubes["RBox"];
	this->cubes["RBox"].fill(position,size,0);

	
	size.x = 5;
	size.y = 5;
	position.fill(-5,3,-5);
	color.fill(1,0,1);
	vector3 speed(0.05f,0,0);
	for (int i = 0; i < killers; i++)
	{
		this->killers[i];
		this->killers[i].fill(position,size,color,0);
		this->killers[i].initlize(position,speed,goombaDist);
		this->killers[i].speed.x = 0.05f;
	}

	masterBullet.setColor(1,0,0);

	for (int i = 0; i < trees; i++)
	{
		this->trees[i].init(-90 + (i * 20),0,0,20,10);
	}
	
	srand (time(0));
	vector3 goombaLoc(10,0,10);
	vector3 goombaSpeed(0.1f,0,0);
	//0.5 is pretty fast btw

	for (int i = 0; i < goombas; i++)
	{
		switch(i)
		{
		case 1:
		goombaLoc.x = rand() % -80 + 80;
			break;
		case 2:
		goombaLoc.z = rand() % -80 + 80;
		case 3:
		goombaLoc.x = rand() % -80 + 80;
		break;
		default:
		goombaLoc.z = rand() % -80 + 80;
		goombaLoc.x = rand() % -80 + 80;
			break;
		}
		this->goombas[i].initlize(goombaLoc,goombaSpeed,goombaDist);
	}
	reloadGun = false;
}

void MapCollection::draw(void)
{
	switch(curr)
	{
	case GAME:
		{
			typedef std::map<int, Tree>::iterator it_tree;
			for(it_tree iterator = trees.begin(); iterator != trees.end(); iterator++) 
			{
				iterator->second.draw();
			}
	
			typedef std::map<std::string, Cube>::iterator it_cube;
			for(it_cube iterator = cubes.begin(); iterator != cubes.end(); iterator++) 
			{
				if (iterator->second.color.x <= 0 && iterator->second.color.y <= 0 && iterator->second.color.z <= 0)
					iterator->second.draw(0,0,0);
				else
					iterator->second.draw();
			}
			typedef std::map<int, Bullet>::iterator it_bullet;
			for(it_bullet iterator = bullets.begin(); iterator != bullets.end(); iterator++) 
			{
				iterator->second.draw();
			}
			typedef std::map<int, Goomba>::iterator it_goomba;
			for(it_goomba iterator = goombas.begin(); iterator != goombas.end(); iterator++) 
			{
				iterator->second.draw();
			}
			typedef std::map<int, Killer>::iterator it_killer;
			for(it_killer iterator = killers.begin(); iterator != killers.end(); iterator++) 
			{
				iterator->second.draw();
			}
			break;}
	case OPTIONS:
		{
			break;}
	case SPLASH:
		{
			break;}
	case MENU:
		{
			break;}
	case EXIT:
		{
			break;}
	}
}

bool MapCollection::update(vector3 & playerSpeed,vector3 & playerPos, vector3 & playerSize, int & jump, float & invtimer,float & playerHealth)
{
	//std::string output = std::to_string(static_cast<long long>(playerPos.x)) + "," + std::to_string(static_cast<long long>(playerPos.y)) + "," + std::to_string(static_cast<long long>(playerPos.z));
	//std::cout << output << "\n";// << "/n";
	switch(curr)
	{
	case GAME:
		{
			if (playerHealth <= 0)
				curr = EXIT;
			vector3 size(20,5,20);	
			typedef std::map<int, Tree>::iterator it_type;
			Collision coll;
			Collision playerColl(playerSpeed,playerPos,playerPos,1);
			bool floorColl = false;

			for(it_type iterator = trees.begin(); iterator != trees.end(); iterator++) 
			{

				float radius = 10;
		
				coll.vecCenter = iterator->second.position;// + iterator->second.speed;
				coll.radius = iterator->second.base.base;
				coll.speed = playerSpeed;
				coll.position = playerPos;

				bool xCollide = (playerPos.x + playerSpeed.x >= iterator->second.base.position.x) && (playerPos.x + playerSpeed.x  <=  iterator->second.base.position.x);
				bool zCollide = (playerPos.z + playerSpeed.z >= iterator->second.base.position.z) && (playerPos.z + playerSpeed.z <=  iterator->second.base.position.z);
				vector3 pos(playerPos.x + playerSpeed.x,playerPos.y,playerPos.z);
				if (CheckBoxCollision(pos,iterator->second.base.position,playerSize,size))
					playerSpeed.x = 0;
				vector3 posz(playerPos.x,playerPos.y,playerPos.z + playerSpeed.z);
				if (CheckBoxCollision(posz,iterator->second.base.position,playerSize,size))
					playerSpeed.z = 0;

			}
			typedef std::map<std::string, Cube>::iterator it_cube;
			for(it_cube iterator = cubes.begin(); iterator != cubes.end(); iterator++) 
			{
				/*if (playerPos.y - playerSize.y > iterator->second.position.y + iterator->second.size.y && 
					playerPos.y - playerSize.y < iterator->second.position.y + iterator->second.size.y + 5 && 
					playerPos.x >= iterator->second.position.x && 
					playerPos.x <=iterator->second.position.x + iterator->second.size.x &&
					playerPos.z >= iterator->second.position.z && 
					playerPos.z <=iterator->second.position.z + iterator->second.size.x &&
					iterator->first == "RBox")

					floorColl = true;
				*/
				//Collision boxColl(iterator->second.speed,iterator->second.position,iterator->second.position,iterator->second.size.x/2);
				//if (!playerColl.checkSquareToSquareX(boxColl))
				//	playerSpeed.x = 0;
				//if (!playerColl.checkSquareToSquareZ(boxColl))
				//	playerSpeed.z = 0;

				iterator->second.update();
			}
			std::map<int, Goomba>::iterator it_goomba = goombas.begin();
			std::map<int, Bullet>::iterator it_bullet = bullets.begin();
	
			//Go though the bullet map and check against the other maps.
			while (it_bullet != bullets.end())
			{
				if ((*it_bullet).second.killOff)
				{
					std::cout << "Erasing bullet: " << it_bullet->first;
					std::map<int, Bullet>::iterator toErase = it_bullet;
					++it_bullet;
					bullets.erase(toErase);
				}else
				{
					it_bullet->second.updateSpeed();
					it_bullet->second.update();
					while(it_goomba != goombas.end() && it_bullet->second.killOff != true)
					{
						Collision bulletCollision((it_bullet->second.speed),(it_bullet->second.position),(it_goomba->second.position),10);
						if (bulletCollision.mSphereCollision())
						{
							it_bullet->second.killOff = true;
							it_goomba->second.killOff = true;
						}
						++it_goomba;
					}
					++it_bullet;
				}
			}

			//Go though the Goomba map and check against the other maps.
			it_goomba = goombas.begin();
			while(it_goomba != goombas.end())
			{
				if ((*it_goomba).second.killOff)
				{
					std::map<int, Goomba>::iterator toErase = it_goomba;
					++it_goomba;
					goombas.erase(toErase);
				}
				else
				{
				it_goomba->second.update();
				if (invtimer == 0)
				{
					Collision playerCllision((playerSpeed),(playerPos),(it_goomba->second.position),10);
					if (playerCllision.mSphereCollision())
					{
						invtimer = 100;
						playerHealth -= 8;
					}
				}
				++it_goomba;
				}
			}
			typedef std::map<int, Killer>::iterator it_killer;
			for(it_killer iterator = killers.begin(); iterator != killers.end(); iterator++) 
			{
				iterator->second.update();
			}
			return floorColl;
			break;}
	case OPTIONS:
		{
			break;}
	case SPLASH:
		{
			break;}
	case MENU:
		{
			break;}
	case EXIT:
		{
			break;}
	}
	return true;
}

bool MapCollection::check_collision(float x,float y,float xx, float yy, vector3 size, vector3 sizeTwo)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = x;
	rightA = x + size.x;
    topA = y;
    bottomA = y + size.y;
        
    //Calculate the sides of rect B
    leftB = xx;
    rightB = xx + sizeTwo.x;
    topB = yy;
	bottomB = yy + sizeTwo.y;
	if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}
bool MapCollection::check_diff(int n1, int n2, int fat) {
	return ( ( (n2>n1) & (n2-fat<n1) ) | ( (n2<n1) & (n2+fat>n1) ) );
}
bool MapCollection::CheckBoxCollision( vector3 PointA, vector3 PointB, vector3 SizeA, vector3 SizeB) 
{
return (check_diff(PointA.x, PointB.x, SizeA.x) && 
	check_diff(PointA.y, PointB.y, SizeA.y) && 
	check_diff(PointA.z, PointB.z, SizeA.x) 
	|| 
	check_diff(PointB.x, PointA.x, SizeB.x) &&
	check_diff(PointB.y, PointA.y, SizeB.y) && 
	check_diff(PointB.z, PointA.z, SizeB.x) ) ; 
}
bool MapCollection::testRadialCollision(vector3 & speed,vector3 & position,float & radius,vector3 & speedTwo,vector3 & positionTwo,float & radiusTwo,vector3 & sizeTwo)
{
	float r = radius + radiusTwo;

	if ((position - positionTwo).magnitudeSqured() < r * r && position.y < positionTwo.y + sizeTwo.y)
	{
		vector3 netVelocity = speed - speedTwo;
		vector3 displacement = position - positionTwo;

		return netVelocity.dot(displacement) < 0;
	}
	else
		return false;
}

void MapCollection::fireBullet(vector3 & playerPos,float angle, float lx,float ly, float lz)
{
	if (whatBullet < 10)
	{
		whatBullet++;
		Bullet newBullet(masterBullet);
		newBullet.angle = angle;
		newBullet.position = playerPos;
		newBullet.size.x = 3;
		newBullet.size.y = 2;
		newBullet.speed.x = lx * 0.5f;
		newBullet.speed.z = lz * 0.5f;
		newBullet.speed.y = ly * 0.5f;
		newBullet.position.y = playerPos.y;
		bullets[whatBullet] << newBullet;
	}
	else
		reloadGun = true;
}
void MapCollection::reload()
{
	reloadGun = false;
	whatBullet = 1;
}