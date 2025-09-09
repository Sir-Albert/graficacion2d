#include "linea.h"
#include "draw.h"

void draw_line(int x0,int y0,int x1,int y1,uint32_t color)
{
	//fuerza_bruta(x0,y0,x1,y1,color);
	//dda(x0,y0,x1,y1,color);
	bressenham(x0,y0,x1,y1,color);
}

void fuerza_bruta(int x0,int y0,int x1,int y1,uint32_t color)
{
	int x,y;	
	float dx = x1-x0;
	float dy = y1-y0;
	for( x = x0; x <= x1; x++)
	{
		y = y0 +  dy  * ((x-x0)/dx);
		draw_pixel(x,y,color);
	}
}


void dda(int x0,int y0,int x1,int y1,uint32_t color)
{
	int dx = x1-x0;
	int dy = y1-y0;
	int abs_dx =  (dx<0) ? (dx*-1):dx ;
	int abs_dy =  (dy<0) ? (dy*-1):dy ;	
	int largo  = (abs_dx > abs_dy) ? abs_dx:abs_dy;
	float inc_x = dx / (float)largo;
	float inc_y = dy / (float)largo;
	float x = x0;
	float y = y0;
	int i,rx,ry;
	for( i = 0; i < largo; i++)
	{
		rx =(  ( x - (int)x )  > 0.5 ) ? ((int)x ) + 1:(int) x;
		ry =(  ( y - (int)y )  > 0.5 ) ? ((int)y ) + 1:(int) y;
		draw_pixel(rx,ry,color);
		x+=inc_x;
		y+=inc_y;
	}
}


void bressenham(int x0,int y0,int x1,int y1,uint32_t color)
{
	int dx =  (x1-x0<0) ? -(x1-x0):x1-x0;
	int sx =  (x0 < x1 ) ? 1 : -1;
	int dy =  (y1-y0>0) ? -(y1-y0):y1-y0;
	int sy =  (y0 < y1 ) ? 1 : -1;
	int error = dx + dy;
	int x = x0;
	int y = y0;
	while(1)
	{
		draw_pixel(x,y,color);
		if( x == x1 && y == y1)break;
		int e2 = 2 * error;
		if( e2 >= dy )
		{
			error += dy;
			x += sx;
		}
		if( e2 <= dx)
		{
			error += dx;
			y += sy;			
		}
	}	
}


