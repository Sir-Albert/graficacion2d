#include "global.h"
#include "color/colores.h"

EstadoRender estadosrender ={
	.evento = {0},
	.textura = 0,
	.renderer = 0,
	.color_buffer = 0,
	.ven_width = 1080,
	.ven_height = 720,
	.clear_color = {0x000000FF},
	.run = 1,	
	.figuras_buffer = 0
};