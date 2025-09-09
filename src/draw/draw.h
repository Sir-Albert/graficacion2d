//draw.h
#ifndef DRAW_H
#define DRAW_H

#include <stdint.h>

#include "Figuras.h"
#include "../color/colores.h"
#include "../math/vectores.h"


void draw_pixel(int x, int y, uint32_t color);
void draw_points(int steps, uint32_t color);
void draw_horizontal(int steps, uint32_t color);
void draw_grid(int steps, uint32_t color);


void draw_points_lerp(int steps, Color colorA,Color colorB);
void draw_horizontal_lerp(int steps, Color colorA,Color colorB);
void draw_grid_lerp(int steps, Color colorA,Color colorB);

void draw_line(int x0,int y0,int x1,int y1,uint32_t color);
void draw_rect(int x0,int y0,int w,int h,uint32_t color);
void draw_trian(int *xs,int *ys,uint32_t color);
void draw_circle_vert(int x,int y,int r, int vert,uint32_t color);
void draw_circle(int xc,int yc,int r,uint32_t color);


void draw_linea_lerp(Vec2 p0,Vec2 p1,uint32_t color);
void draw_curva(Vec2 p0,Vec2 p1,Vec2 p2,uint32_t color);



void draw_figura(Figuras *fig);

void fill_trian(Triangulo trian,uint32_t color);
void fill_figura(Figuras fig,uint32_t color);
#endif