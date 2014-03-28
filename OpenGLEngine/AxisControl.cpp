#include "stdafx.h"
#include "AxisControl.h"



Block::Block()
{

}
Block::~Block()
{

}

void Block::drawTex()
{
	cube.drawTex();
}
void Block::drawModel()
{
	//cube.drawModel();
}
void Block::update(vector3 playerPos)
{
	cube.update(0, playerPos);
}
/*int Block::LoadGLTextures()
{
	return 0;
}
int Block::LoadGLTextures(int limit)
{
	return 0;
}*/


Air::Air()
{

}
Air::~Air()
{

}

GenericSolid::GenericSolid()
{

}
GenericSolid::~GenericSolid()
{

}

GenericPassable::GenericPassable()
{

}
GenericPassable::~GenericPassable()
{

}











AxisControl::AxisControl()
{

}
AxisControl::~AxisControl()
{
}

template <class objectType>
//void setElement(int pos, objectType obj);
void AxisControl::setElement(int x,int y, objectType obj)
{
	chunks[x].at(y) = obj;
}

void AxisControl::init(vector3 playerPos)
{
	/*axis = std::vector<Block*>(50);
	int count = 0;
	for (unsigned i = 0; i < axis.size()/5; i++)
	for (unsigned ii = 0; ii < axis.size()/10; ii++)
	{
		axis.at(count) = new GenericSolid();
		axis.at(count)->cube = Cube((playerPos.x + (12.5 * 10)) - (i * 10), 0, (playerPos.x + (12.5 * 10)) - (ii * 10), 10, 10);
		axis.at(count)->cube.filename = "gs.png";
		axis.at(count)->cube.init();
		axis.at(count)->cube.update();
		axis.at(count)->collidable = true;
		count++;
	}*/
	playerPos.empty();

	/*chunks = std::vector<std::vector<Block*>(25)>(25);
	int count = 0;
	for (unsigned i = 0; i < chunks.size() / 5; i++)
		for (unsigned ii = 0; ii < chunks.size() / 10; ii++)
		{
			chunks.at(count) = new GenericSolid();
			int breadth = 15;
			chunks.at(count)->cube = Cube(((12.5 * breadth)) - (i * breadth), breadth/2, ((12.5 * breadth)) - (ii * breadth), breadth, breadth);
			chunks.at(count)->cube.filename = "gs.png";
			chunks.at(count)->cube.init();
			chunks.at(count)->cube.update();
			chunks.at(count)->collidable = true;
			chunks.at(count)->positioning.x = i;
			chunks.at(count)->positioning.z = ii;
			count++;
		}*/
	chunks.resize(5);
	for (auto i = 0; i < chunks.size(); i++)
	{
		//new vector block pointer
		std::vector<Block*> nvbp;
		nvbp = std::vector<Block*>(5);
		for (unsigned ii = 0; ii < nvbp.size(); ii++)
		{
			nvbp.at(ii) = new GenericSolid();
			int breadth = 10;
			nvbp.at(ii)->cube = Cube(((12.5 * breadth)) - (i * breadth), breadth / 2, ((12.5 * breadth)) - (ii * breadth), breadth, breadth);
			nvbp.at(ii)->cube.filename = "gs.png";
			nvbp.at(ii)->cube.init();
			nvbp.at(ii)->cube.update();
			nvbp.at(ii)->collidable = true;
			nvbp.at(ii)->positioning.x = i;
			nvbp.at(ii)->positioning.z = ii;
			
		}
		chunks[i] = (nvbp);

	}

	//blankSolid.position = starting;
}
vector3 calculatePositioning(vector3 position)
{
	vector3 result = vector3((int)(position.x / 15), 0, (int)(position.z / 15));
	return result;
}

void AxisControl::drawTex()
{
	/*for (auto & element : chunks) {
		if (element->distance < 200)
			element->drawTex();
		//else
		//	element->drawModel();
	}*/
	/*for (auto & i : chunks)
	{
		for (auto & ii : i)
		{
			if (ii->distance < 200)
				ii->drawTex();
		}
	}*/

	if (pPositioning.x > 4 || pPositioning.x < 0 || pPositioning.y > 4 || pPositioning.y < 0)
		return;

	for (auto & i : chunks)
	{
		for (auto & ii : i)
		{
			if (ii->distance < 200)
				ii->drawTex();
		}
	}
	/*for (auto & element : chunks[pPositioning.x]) 
		if (element->distance < 200)
			element->drawTex();*/
	//chunks[pPositioning.x][pPositioning.y]->drawTex();
}
void AxisControl::update(vector3 playerPos)
{
	pPositioning = calculatePositioning(playerPos);
	if (pPositioning.x > 4 || pPositioning.x < 0 || pPositioning.y > 4 || pPositioning.y < 0)
		return;
	chunks[pPositioning.x][pPositioning.y]->update(playerPos);
	/*for (auto & i : chunks)
	{
		for (auto & ii : i)
		{
			if (ii->distance < 100)
				ii->update(playerPos);
		}
	}*/
	//for (auto & element : chunks) {
	//	element->distance = sqrt((playerPos.x - element->cube.position.x)*(playerPos.x - element->cube.position.x)/* + (playerPos.y - element->cube.position.y)*(playerPos.y - element->cube.position.y)*/ + (playerPos.z - element->cube.position.z)*(playerPos.z - element->cube.position.z));
	//	if (element->distance < 100)
	//	element->update(playerPos);
	//}
}
