#pragma once
#include "basicshape.h"
#include "VectorLib.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl\GLU.h>
#define MAX_VERTICES 20 
#define MAX_POLYGONS 20

typedef struct{
    float x,y,z;
}vertex_type;

typedef struct{
    int a,b,c;
	void set(int a, int b, int c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}
}polygon_type;

class Cube :
	public BasicShape
{
public:
	Cube(void);
	Cube(float x, float y,float z,float width,float height);
	~Cube(void);

	//void init(
	void update();
	void draw(void);
	void draw(GLfloat r, GLfloat g, GLfloat b);
	void draw(GLfloat r, GLfloat g, GLfloat b,GLfloat rr, GLfloat gg, GLfloat bb,GLfloat rrr, GLfloat ggg, GLfloat bbb);
	void fill(vector3 position, vector2 size, vector3 color, float angle);
	void fill(vector3 position, vector2 size, float angle);
	void setColor(GLfloat r,GLfloat g,GLfloat b);

	vector3 position;
	vector3 color;
	vector2 size;

	float angle;
	bool floor;

	vertex_type vertex[MAX_VERTICES]; 
    polygon_type polygon[MAX_POLYGONS];
};

