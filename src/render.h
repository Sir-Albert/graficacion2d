//render.h
#ifndef RENDER_H
#define RENDER_H
/*
	Archivo interfaz para
	mostrar en pantalla
*/

#include <stdint.h>
#include "global.h"
#include "draw/figuras.h"
#include "math/vectores.h"

void update(void);
void copy_buffer_to_texture(void);
void _init(void);
void clear_color_buffer(void);
void render_frame(void);
void render_input(void);
Vec2 *pivote_mas_cercano(Vec2 mp,Figuras *figs,float umbral);


#endif