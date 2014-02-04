#pragma once
#include "basicshape.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl\GLU.h>

class Cone :
	public BasicShape
{
public:
	Cone(void);
	Cone(int x, int y, int z);
	Cone(vector3 change);
	Cone(int x, int y, int z,float base,int height);
	Cone(vector3 change,float base,int height);
	~Cone(void);

	void init(int x, int y, int z);
	void init(vector3 change);
	void init(int x, int y, int z,float base,int height);
	void init(vector3 change,float base,int height);
	
	void fill(vector3 position, vector2 size, vector3 color);
	void fill(vector3 position, vector2 size);

	void draw(void);
	void draw(GLfloat r,GLfloat g,GLfloat b);

	void update(void);

	int height;
	float base;
	vector3 color;
};

