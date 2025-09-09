#include "lerp.h"


Vec2 lerpVector2D(Vec2 p0,Vec2 p1,float t)
{
	Vec2 localV2;
	localV2.unpack.x = (1-t)*p0.unpack.x + (t*p1.unpack.x);	
	localV2.unpack.y = (1-t)*p0.unpack.y + (t*p1.unpack.y);
	return localV2;
}

Vec2 lerp2Vector2D(Vec2 p0,Vec2 p1,Vec2 p2,float t)
{
	Vec2 localV2;	
	float t2 = ((1-t)*(1-t));
	localV2.unpack.x = t2*p0.unpack.x + (2*(1-t)*t*p1.unpack.x) + (t*t*p2.unpack.x);	
	localV2.unpack.y = t2*p0.unpack.y + (2*(1-t)*t*p1.unpack.y) + (t*t*p2.unpack.y);
	return localV2;
}