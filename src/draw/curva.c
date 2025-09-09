#include "draw.h"
#include "linea.h"
#include "../math/vectores.h"
#include "../math/lerp.h"

#include <math.h>

void draw_linea_lerp(Vec2 p0,Vec2 p1,uint32_t color)
{	
	Vec2 drawV2;
	float t;
	int x,y;
	for( t = 0; t <= 1; t+=0.001)
	{
		drawV2 =lerpVector2D(p0,p1,t);
		x = roundf(drawV2.unpack.x);
		y = roundf(drawV2.unpack.y);
		draw_pixel(x,y,color);
	}	
}
void draw_curva(Vec2 p0,Vec2 p1,Vec2 p2,uint32_t color)
{
	Vec2 drawV2;
	float t;
	int x,y;
	for( t = 0; t <= 1; t+=0.001)
	{
		drawV2 =lerp2Vector2D(p0,p1,p2,t);
		x = roundf(drawV2.unpack.x);
		y = roundf(drawV2.unpack.y);
		draw_pixel(x,y,color);
	}
}

