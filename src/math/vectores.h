#ifndef VECTORES_H
#define VECTORES_H
#include <math.h>
typedef union
{
	float data[2];
	struct
	{
		float x,y;
	}unpack;
}Vec2;

typedef struct
{
	float data[3];
	struct
	{		
		float x,y,z;
	}unpack;
}Vec3;

float distanciaV2(Vec2 p1,Vec2 p2);

#endif