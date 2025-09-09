//colores.c
#include "colores.h"

Color ROJO = {0xFF0000FF};
Color VERDE = {0x00FF00FF};
Color AZUL = {0x0000FFFF};
Color CYAN = {0x00FFFFFF};
Color NEGRO = {0x000000FF};
Color BLANCO = {0xFFFFFFFF};


Color lerp_color(Color a,Color b,float increment)
{
	Color nuevo;
	nuevo.rgba.r = a.rgba.r + ( b.rgba.r - a.rgba.r) * increment;
	nuevo.rgba.g = a.rgba.g + ( b.rgba.g - a.rgba.g) * increment;
	nuevo.rgba.b = a.rgba.b + ( b.rgba.b - a.rgba.b) * increment;
	nuevo.rgba.a = 0xFF;
	return nuevo;
}