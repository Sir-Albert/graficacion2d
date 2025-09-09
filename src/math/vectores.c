#include "vectores.h"


float distanciaV2(Vec2 p1,Vec2 p2)
{
	return sqrt( pow(p2.unpack.x-p1.unpack.x,2)+pow(p2.unpack.y-p1.unpack.y,2));
}