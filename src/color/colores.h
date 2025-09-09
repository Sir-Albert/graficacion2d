//colores.h
#ifndef COLORES_H
#define COLORES_H

#include <stdint.h>

typedef union color
{
	uint32_t hex;
	struct
	{
		uint8_t a;
		uint8_t b;
		uint8_t g;
		uint8_t r;
	}rgba;
}Color;


extern Color ROJO;
extern Color VERDE;
extern Color AZUL;
extern Color CYAN;
extern Color BLANCO;
extern Color NEGRO;


Color lerp_color(Color a,Color b,float increment);



#endif