#ifndef FIGURAS_H
#define FIGURAS_H

#include <stdint.h>
#include "../color/colores.h"
#include "../math/vectores.h"

typedef enum
{
	LINEA = 2<<0,
	CURVA = 2<<1,
	CUADRO = 2<<2,
	TRIAN = 2<<3,
	CIRC = 2<<4
}TypeFig;


typedef struct
{	
	char offset[28];
	TypeFig type;	
}FigComun;

typedef struct
{
	Vec2 p0;
	Vec2 p1;
	char offset_mem1[8];
	Color color;
	TypeFig type;
}Linea;

typedef struct
{
	Vec2 p0;
	Vec2 p1;
	Vec2 p2;
	Color color;
	TypeFig type;	
}Curva;

typedef struct
{
	Vec2 pos;
	int width;
	int height;
	char offset_mem1[8];
	Color color;
	TypeFig type;
}Cuadro;

typedef struct
{	
	Vec2 p0;
	Vec2 p1;
	Vec2 p2;	
	Color color;
	TypeFig type;	
	
}Triangulo;

typedef struct
{	
	Vec2 pos;
	float radio;
	char offset_mem1[12];
	Color color;
	TypeFig type;	
}Circulo;


typedef union
{
	FigComun data;
	Linea linea;
	Curva curva;
	Cuadro cuadro;
	Triangulo triangulo;
	Circulo circulo;
}Figuras;


void print_figtype(Figuras fig);



#endif