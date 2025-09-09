//render.c

#include "render.h"
#include "color/colores.h"
#include "draw/draw.h"
#include "draw/Figuras.h"
#include "math/vectores.h"
#include "memoria/memoria.h"

Vec2 *pivote;

Vec2 *pivote_mas_cercano(Vec2 mp,Figuras *figs,float umbral)
{
	int i;
	int a = 0;
	int b = array_size(figs)-1;
	float low,high;
	float cercano = 99999999999.f;
	Figuras *res = NULL;
	
	for( i = 0; i < array_size(figs) ;i++)
	{
		low = distanciaV2(mp,figs[a].cuadro.pos);
		high= distanciaV2(mp,figs[b].cuadro.pos);			
		if(fabs(low)<fabs(cercano) && fabs(low)<= umbral)
		{
			res = &figs[a];
		    cercano= distanciaV2(mp,figs[a].cuadro.pos);
		}
		if(fabs(high)<fabs(cercano) && fabs(high)<= umbral)
		{
			res = &figs[b];
			cercano= distanciaV2(mp,figs[b].cuadro.pos);
		}
		b--;
		a++;
		if(b < a)
			break;		
	}
	if(res)
		print_figtype(*res);
	return (res) ?  &(res->cuadro.pos):NULL;
}


void render_input(void)
{
	if(estadosrender.evento.type == SDL_EVENT_QUIT)
	{
		estadosrender.run = 0;
	}
	
	if(estadosrender.evento.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
	{
		//BUSCAR PIVOTE MAS CERCA DEL MOUSE
		printf("\n (%.3f,%.3f)",estadosrender.evento.motion.x,estadosrender.evento.motion.y);
		Vec2 mp = {{estadosrender.evento.motion.x,estadosrender.evento.motion.y}};
		pivote = pivote_mas_cercano(mp,estadosrender.figuras_buffer,10.f);
		if(pivote)
			printf("\n Mas cerca(%.3f,%.3f)",pivote->unpack.x,pivote->unpack.y);
		
		//OBTENER REFERENCIA DE LA FIGURA
		
	}
	else if(estadosrender.evento.type == SDL_EVENT_MOUSE_BUTTON_UP)
	{
		//MODIFICAR FIGURA
	}
	
}

void _init(void)
{
		
	int px = estadosrender.ven_width/2;
	int py = estadosrender.ven_height/2;
	
	Linea linea = 
	{
		.p0 = (Vec2){{px,py}},
		.p1 = (Vec2){{px + 200,py + 50}},
		.offset_mem1 = {0},
		.color = AZUL,
		.type = LINEA
	};	
	Curva curva = 
	{
		.p0 = (Vec2){{px,py}},
		.p1 = (Vec2){{px-200,py-50}},
		.p2 = (Vec2){{px-100,py-100}},
		.color = AZUL,
		.type = CURVA
	};
	Cuadro cuadro =
	{
		.pos = (Vec2){{300,300}},
		.width = 200,
		.height = 200,
		.offset_mem1 = {0},
		.color = VERDE,
		.type = CUADRO
	};
	Triangulo triangulo1 =
	{
		.p0 = (Vec2){{550,250}},
		.p1 = (Vec2){{750,200}},
		.p2 = (Vec2){{650,100}},
		.color = CYAN,
		.type = TRIAN
	};	
	Circulo circulo = 
	{
		.pos = (Vec2){{px,py}},
		.radio = 300,
		.offset_mem1 = {0},
		.color = ROJO,
		.type = CIRC
	};
	Triangulo triangulo2 =
	{
		.p0 = (Vec2){{100,250}},
		.p1 = (Vec2){{200,250}},
		.p2 = (Vec2){{50,100}},
		.color = VERDE,
		.type = TRIAN
	};	
	Triangulo triangulo3 =
	{
		.p0 = (Vec2){{100,400}},
		.p1 = (Vec2){{200,400}},
		.p2 = (Vec2){{50,500}},
		.color = BLANCO,
		.type = TRIAN
	};
	
	pushto_array( estadosrender.figuras_buffer , (Figuras){.circulo = circulo}    );
	pushto_array( estadosrender.figuras_buffer , (Figuras){.cuadro = cuadro}      );
	pushto_array( estadosrender.figuras_buffer , (Figuras){.triangulo = triangulo1});
	pushto_array( estadosrender.figuras_buffer , (Figuras){.triangulo = triangulo2});
	pushto_array( estadosrender.figuras_buffer , (Figuras){.triangulo = triangulo3})
	pushto_array( estadosrender.figuras_buffer , (Figuras){.linea = linea}        );    
	pushto_array( estadosrender.figuras_buffer , (Figuras){.curva = curva}        );;
	
}


void update(void)
{		
	int i;
	//draw_points(10,VERDE.hex);	
	draw_points_lerp(10,AZUL,VERDE);
	for( i = 0 ; i < array_size(estadosrender.figuras_buffer) ; i++)
	{
		draw_figura(&estadosrender.figuras_buffer[i]);
		if(estadosrender.figuras_buffer[i].data.type == TRIAN)
			fill_trian(estadosrender.figuras_buffer[i].triangulo,estadosrender.figuras_buffer[i].triangulo.color.hex);
		if(estadosrender.figuras_buffer[i].data.type == CUADRO)
			fill_figura(estadosrender.figuras_buffer[i],estadosrender.figuras_buffer[i].cuadro.color.hex);
		if(estadosrender.figuras_buffer[i].data.type == CIRC)
			fill_figura(estadosrender.figuras_buffer[i],estadosrender.figuras_buffer[i].circulo.color.hex);
	}
	
}

void copy_buffer_to_texture(void)
{
	SDL_UpdateTexture(estadosrender.textura,NULL,estadosrender.color_buffer,(int)estadosrender.ven_width*sizeof(int));	
	SDL_RenderTexture(estadosrender.renderer,estadosrender.textura,NULL,NULL);
}

void clear_color_buffer(void)
{
	int x,y;
	for(y=0;y<estadosrender.ven_height;++y)
	{
		for(x=0;x<estadosrender.ven_width;++x)
		{
			draw_pixel(x,y,estadosrender.clear_color.hex);
			//estadosrender.color_buffer[y*estadosrender.ven_width+x] = color;
		}
	}	
}

void render_frame(void)
{
	SDL_RenderPresent(estadosrender.renderer);
}