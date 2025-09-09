//pixel.c
#include "draw.h"
#include "../global.h"

void draw_pixel(int x, int y, uint32_t color)
{
	if( x<0 || y<0) return;
	if( x>=estadosrender.ven_width  || y>=estadosrender.ven_height) return;
	estadosrender.color_buffer[y*estadosrender.ven_width+x] = color;
}


void draw_points(int steps, uint32_t color)
{
	int x,y;
	for( y = 0 ; y < estadosrender.ven_height ; ++y)
	{
		for( x = 0	; x < estadosrender.ven_width ; ++x)
		{
			if(x%steps==0 && y%steps==0)
				draw_pixel(x,y,color);	
		}
		
	}	
}

void draw_horizontal(int steps, uint32_t color)
{
	int x,y;
	for( y = 0 ; y < estadosrender.ven_height ; y+=steps)
	{
		for( x = 0	; x < estadosrender.ven_width ; ++x)
			draw_pixel(x,y,color);	
	}	
}
void draw_grid(int steps, uint32_t color)
{
	int x,y;
	for( y = 0 ; y < estadosrender.ven_height ; ++y)
	{
		for( x = 0	; x < estadosrender.ven_width ; ++x )
		{			
			if(x%steps==0 || y%steps==0)
				draw_pixel(x,y,color);
			if(y%steps!=0)
				x += steps-1;	
		}
	}	
}

void draw_points_lerp(int steps, Color colorA,Color colorB)
{
	float t;	
	int x,y;
	for( y = 0 ; y < estadosrender.ven_height ; ++y)
	{
		for( x = 0	; x < estadosrender.ven_width ; ++x)
		{
			t = x/(float)estadosrender.ven_width;
			if(x%steps==0 && y%steps==0)
				draw_pixel(x,y,  lerp_color(colorA,colorB,t).hex);
		}
		
	}	
}
void draw_horizontal_lerp(int steps, Color colorA,Color colorB)
{
	float t;
	int x,y;
	for( y = 0 ; y < estadosrender.ven_height ; y+=steps)
	{
		for( x = 0	; x < estadosrender.ven_width ; ++x)
		{
			t = x/(float)estadosrender.ven_width;
			draw_pixel(x,y,  lerp_color(colorA,colorB,t).hex);
		}
	}	
}
void draw_grid_lerp(int steps, Color colorA,Color colorB)
{
	float t;
	int x,y;
	for( y = 0 ; y < estadosrender.ven_height ; ++y)
	{
		for( x = 0	; x < estadosrender.ven_width ; ++x )
		{			
			t = x/(float)estadosrender.ven_width;
			if(x%steps==0 || y%steps==0)
				draw_pixel(x,y,  lerp_color(colorA,colorB,t).hex);
			if(y%steps!=0)
				x += steps-1;	
		}
	}		
}
