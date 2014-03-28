#pragma once
#include <vector>
#include <memory>
#include "VectorLib.h"
#include "glut.h"
#include "SOIL.h"
#include "Cube.h"
//#define MAX_VERTICES 20 
//#define MAX_POLYGONS 20

using namespace std;


/*
typedef struct{
	float x, y, z;
}vertex_type;

typedef struct{
	int a, b, c;
	void set(int a, int b, int c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}
}polygon_type;
*/


//TODO
class Block
{
public:
	Block();
	~Block();
	void drawTex();
	void drawModel();
	//TODO
	void drawRaw();
	void update(vector3 playerPos);
	vector3 positioning;
	Cube cube;
	bool collidable;
	float distance;
};
//TODO
class Air : public Block
{
public:
	Air();
	~Air();
	//Cube cube;
};
//TODO
class GenericSolid : public Block
{
public:
	GenericSolid();
	~GenericSolid();
	//Cube cube;
};
//TODO
class GenericPassable : public Block
{
public:
	GenericPassable();
	~GenericPassable();
	//Cube cube;
};


class AxisControl
{
public:
	AxisControl();
	//template <class objectType> AxisControl(objectType obj);
	~AxisControl();
	template <class objectType>
	void setElement(int x,int y, objectType obj);
	void init(vector3 playerPos);
	void update(vector3 playerPos);
	void drawTex();
	void drawRaw();

	//Player positioning
	vector3 pPositioning;
	std::vector<std::vector<Block*>> chunks;



	//vector<AxisObject<Air>> axis;
	//std::vector<std::unique_ptr<Block>> axis;

};

