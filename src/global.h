//global.h
#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "color/colores.h"
#include "draw/figuras.h"

typedef struct
{
	SDL_Event evento;	
	SDL_Texture *textura; //CANVA
	SDL_Renderer *renderer;
	uint32_t *color_buffer;
	int ven_width;
	int ven_height;
	Color clear_color;
	int run;
	Figuras *figuras_buffer;
}EstadoRender;

extern EstadoRender estadosrender;

#endif