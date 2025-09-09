#include "draw.h"
#include <math.h>

#define PI 3.14159265359


void draw_circle_vert(int x,int y,int r, int vert,uint32_t color)
{
	int i;
	
	for( i = 0; i < vert ; i++)
	{
		float angulo = i * (2*PI) / vert;
		float angulo_s = ((i+1)%vert*(2*PI))/vert;
		int xa = x + cos(angulo)*r;
		int ya = y + sin(angulo)*r;
		int xs = x + cos(angulo_s)*r;
		int ys = y + sin(angulo_s)*r;
		draw_line(xa,ya,xs,ys,color);
	}
	
}

void draw_circle(int xc,int yc,int r,uint32_t color)
{
	int x = 0;
	int y = r ;
	int p = 1 - r ;
	while ( x <= y ) 
	{
		draw_pixel( xc + x , yc + y , color);
		draw_pixel( xc - x , yc + y , color);
		draw_pixel( xc + x , yc - y , color);
		draw_pixel( xc - x , yc - y , color);
		draw_pixel( xc + y , yc + x , color);
		draw_pixel( xc - y , yc + x , color);
		draw_pixel( xc + y , yc - x , color);
		draw_pixel( xc - y , yc - x , color);
		x++;
		if ( p < 0) 
			p += 2* x + 1;
		else
		{
			y--;
			p += 2*( x - y ) + 1;
		}
	}	
}