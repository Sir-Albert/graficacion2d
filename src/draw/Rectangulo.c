#include "draw.h"


void draw_rect(int x0,int y0,int w,int h,uint32_t color)
{
	draw_line(x0,y0,x0+w,y0,color);
	draw_line(x0+w,y0,x0+w,y0+h,color);
	draw_line(x0+w,y0+h,x0,y0+h,color);
	draw_line(x0,y0+h,x0,y0,color);
}