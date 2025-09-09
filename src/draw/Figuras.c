#include "Figuras.h"
#include "draw.h"
#include <stdio.h>
#include <lista/lista.h>
#include <pila/pila.h>
#include "../global.h"

void draw_figura(Figuras *fig)
{
	switch(fig->data.type)
	{
		case LINEA:
		{
			Linea linea = fig->linea;			
			draw_circle(linea.p0.unpack.x,linea.p0.unpack.y,5,linea.color.hex);
			draw_circle(linea.p1.unpack.x,linea.p1.unpack.y,5,linea.color.hex);
			draw_linea_lerp(linea.p0,linea.p1,linea.color.hex);	
			break;
		}
		case CURVA:
		{
			Curva curva = fig->curva;
			draw_circle(curva.p0.unpack.x,curva.p0.unpack.y,5,curva.color.hex);
			draw_circle(curva.p1.unpack.x,curva.p1.unpack.y,5,curva.color.hex);
			draw_circle(curva.p2.unpack.x,curva.p2.unpack.y,5,curva.color.hex);	
			draw_curva(curva.p0,curva.p1,curva.p2,curva.color.hex);
			
			break;
		}
		case CUADRO:
		{
			Cuadro cuadro = fig->cuadro;			
			draw_rect(cuadro.pos.unpack.x,cuadro.pos.unpack.y,cuadro.width,cuadro.height,cuadro.color.hex);
			break;
		}
		case TRIAN:
		{
			Triangulo triangulo = fig->triangulo;
			int xs[3] = {triangulo.p0.unpack.x,triangulo.p1.unpack.x,triangulo.p2.unpack.x};
			int ys[3] = {triangulo.p0.unpack.y,triangulo.p1.unpack.y,triangulo.p2.unpack.y};
			draw_trian(xs,ys,triangulo.color.hex);			
			break;
		}
		case CIRC:
		{
			Circulo circulo = fig->circulo;			
			draw_circle(circulo.pos.unpack.x,circulo.pos.unpack.y,circulo.radio,circulo.color.hex);
			break;
		}
	}
}


void print_figtype(Figuras fig)
{
	printf("\n");
	switch(fig.data.type)
	{
		case LINEA:
		{
			printf("LINEA");
			break;
		}
		case CURVA:
		{
			printf("CURVA");
			break;
		}
		case CUADRO:
		{
			printf("CUADRO");
			break;
		}
		case TRIAN:
		{		
			printf("TRIAN");
			break;
		}
		case CIRC:
		{
			printf("CIRC");
			break;
		}		
	}	
}




Vec2 getVector(uint32_t *offset)
{
	//RETORNA VEC2 con las posiciones x,y
	//correspodientes a una direccion del bloque del color_buffer
	Vec2 vector;
	int pos  = offset - estadosrender.color_buffer;
	vector.unpack.x = pos%estadosrender.ven_width;
	vector.unpack.y = pos/estadosrender.ven_width;
	return vector;	
}

uint32_t* getOffset(Vec2 punto)
{
	//RETORNA DIRECCION perteneciente al bloque de color_buffer
	//dada una coordenada
	return &estadosrender.color_buffer[(int)punto.unpack.y*estadosrender.ven_width+(int)punto.unpack.x];	
}

uint32_t checkColor(Vec2 punto)
{
	//RETORNA el color ubicado en una posicion del color_buffer
	return estadosrender.color_buffer[(int)punto.unpack.y*estadosrender.ven_width+(int)punto.unpack.x];	
}

void fill_figura(Figuras fig,uint32_t relleno)
{
	Pila pila = inicializarPila();
	Vec2 direcciones[4];
	Vec2 vector;
	Color color;
	draw_figura(&fig); //PINTAR CONTORNO
	switch(fig.data.type)
	{
		case LINEA:case CURVA:break;
		case CUADRO:
		{
			if(fig.cuadro.width<=2 || fig.cuadro.height<=2)return;
			//CENTRO CUADRADO
			direcciones[0] = (Vec2){{fig.cuadro.pos.unpack.x+fig.cuadro.width/2,fig.cuadro.pos.unpack.y+fig.cuadro.height/2}}; 
			push(&pila, getOffset(direcciones[0]) );
			break;
		}
		case CIRC:
		{
			if(fig.circulo.radio<=1)return;
			push(&pila, getOffset(fig.circulo.pos) ); //CENTRO CIRCULO
			break;
		}	
		case TRIAN:
		{		
			//FALTA SACAR EL CENTRO DEL TRIANGULO
			//PARA NO USAR FILL TRIAN
			fill_trian(fig.triangulo,relleno);
			return;
		}	
	}	
	while(!vacia(pila))
	{
		//PINTAR
		vector = getVector(pop(&pila)); //OBTIENE LA COORDENADA DEL PIXEL
		draw_pixel(vector.unpack.x,vector.unpack.y,relleno);
		//REVISAR POSIBLE PROPAGACION EN 4 DIRECCIONES
		direcciones[0] = (Vec2){{vector.unpack.x,vector.unpack.y-1}}; //NORTE
		direcciones[1] = (Vec2){{vector.unpack.x+1,vector.unpack.y}}; //ESTE
		direcciones[2] = (Vec2){{vector.unpack.x,vector.unpack.y+1}}; //SUR
		direcciones[3] = (Vec2){{vector.unpack.x-1,vector.unpack.y}}; //OESTE
		int i;
		for(i=0;i<4;i++)
		{				
			color.hex = checkColor(direcciones[i]);	
			//PROPAGAR SI NO ESTA PINTADO
			//COMPARAR CON COLOR RELLENO Y CON COLOR CONTORNO
			if(color.hex != relleno && color.hex != fig.cuadro.color.hex)
				push(&pila,getOffset(direcciones[i]));
		}			
	}		
}

