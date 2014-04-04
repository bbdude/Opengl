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
	for (auto i = 0; i < chunks.size();i++)
		chunks[i].resize(5);
	for (auto i = 0; i < chunks.size();i++)
	for (auto ii = 0; ii < chunks[i].size(); ii++)
	{
		//new vector block pointer
		std::vector<Block*> nvbp;
		nvbp = std::vector<Block*>(25);
		int countx = 0;
		int countz = 0;
		for (unsigned iii = 0; iii < nvbp.size(); iii++)
		{
			if (countz + 1 >= 5)
				countz = 1;
			else
				countz++;
			nvbp.at(iii) = new GenericSolid();
			int breadth = 10;
			//nvbp.at(iii)->cube = Cube(((12.5 * breadth)) - (ii * breadth), (breadth * i) / 2, ((12.5 * breadth)) - (iii * breadth), breadth, breadth);
			nvbp.at(iii)->cube = Cube((((12.5 * breadth)) - ((ii + countx) * breadth)) + ((breadth*5)*i), /*(breadth * i) / 2*/ 0, (((12.5 * breadth)) - (countz * breadth)) + (breadth*i), breadth, breadth);
			nvbp.at(iii)->cube.filename = "gs.png";
			nvbp.at(iii)->cube.init();
			nvbp.at(iii)->cube.update();
			nvbp.at(iii)->collidable = true;
			nvbp.at(iii)->positioning.x = ii;
			nvbp.at(iii)->positioning.z = iii;
			if (iii % 5 == 0)
				countx++;
		}
		//chunks[0].chunks[i] = (nvbp);
		chunks[i].at(ii) = (nvbp);

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
	if (pPositioning.x > 4 || pPositioning.x < 0 || pPositioning.y > 4 || pPositioning.y < 0)
		return;

	for (auto i = 0; i < chunks[pPositioning.x][pPositioning.y].size(); i++)
		chunks[pPositioning.x][pPositioning.y][i]->drawTex();
}
void AxisControl::update(vector3 playerPos)
{
	pPositioning = calculatePositioning(playerPos);
	pPositioning.x -= 6;
	pPositioning.y *= -1;
	std::cout << pPositioning.x;// +"Y:" + "Z:");
	if (pPositioning.x > 4 || pPositioning.x < 0 || pPositioning.y > 4 || pPositioning.y < 0)
		return;
	for (auto i = 0; i < chunks[pPositioning.x][pPositioning.y].size(); i++)
		chunks[pPositioning.x][pPositioning.y][i]->update(playerPos);
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
/*void AxisControl::init(vector3 playerPos)
{

	playerPos.empty();

	chunks.resize(5);
	for (auto i = 0; i < chunks.size(); i++)
		chunks[i].resize(5);
	for (auto i = 0; i < chunks.size(); i++)
		for (auto ii = 0; ii < chunks[i].size(); ii++)
		{
			//new vector block pointer
			std::vector<Block*> nvbp;
			nvbp = std::vector<Block*>(5);
			for (unsigned iii = 0; iii < nvbp.size(); iii++)
			{
				nvbp.at(iii) = new GenericSolid();
				int breadth = 10;
				nvbp.at(iii)->cube = Cube(((12.5 * breadth)) - (ii * breadth), (breadth * i) / 2, ((12.5 * breadth)) - (iii * breadth), breadth, breadth);
				nvbp.at(iii)->cube.filename = "gs.png";
				nvbp.at(iii)->cube.init();
				nvbp.at(iii)->cube.update();
				nvbp.at(iii)->collidable = true;
				nvbp.at(iii)->positioning.x = ii;
				nvbp.at(iii)->positioning.z = iii;

			}
			//chunks[0].chunks[i] = (nvbp);
			chunks[i].at(ii) = (nvbp);

		}

	//blankSolid.position = starting;
}*/