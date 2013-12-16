#pragma once
#include "basicshape.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl\GLU.h>
#include "Cone.h"

class Tree :
	public BasicShape
{
public:
	Tree(void);
	Tree(int x, int y, int z);
	Tree(vector3 change);
	~Tree(void);

	void draw(void);
	void init(int x,int y,int z, float height,float base);

	Cone top;
	Cone middle;
	Cone base;
};

