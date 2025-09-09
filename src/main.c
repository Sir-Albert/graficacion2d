//Prueba.c
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "global.h"
#include "render.h"
#include "draw/Figuras.h"
#include "memoria/memoria.h"
//gcc -Wall -Werror -pedantic -std=c99 src/main.c -I deps/SDL3-3.2.20/i686-w64-mingw32/include -L deps/SDL3-3.2.20/i686-w64-mingw32/lib -lSDL3 -mwindows

// -mwindows : No output en consola
//WIKI SDL3-3
//  funcion SDL_CreateWindowAndRenderer


SDL_Window *ventana;

#define FPS 60
#define FRAME_TARGET_TIME (1000/FPS)
int frame_tiempo_prev = 0;

void render_init(void);
void render_clean(void);
void grabar_imagen(void);

int main(int argc,char **argv)
{	
	int grabar;
	printf("\n Hola mundo");
	render_init();
	_init();
	//CICLO INFINITO
	while(estadosrender.run)
	{
		grabar = 0;
		int delay_frame = FRAME_TARGET_TIME - (SDL_GetTicks()-frame_tiempo_prev);
		if(delay_frame > 0 && delay_frame <= FRAME_TARGET_TIME)
			SDL_Delay(delay_frame);
		//PROCESAR INPUTS
		while(SDL_PollEvent(&estadosrender.evento))
		{
			render_input();
			if(estadosrender.evento.type == SDL_EVENT_KEY_DOWN)
			{
				if(estadosrender.evento.key.scancode == SDL_SCANCODE_1)
				{
					grabar = 1;
				}
			}
		}	
		update();
		if(grabar)
		{
			grabar_imagen();
			printf("\n SE GRABO IMAGEN");
			grabar = 0;
		}
		copy_buffer_to_texture();
		clear_color_buffer();
		render_frame();
		//frame_tiempo_prev = delay_frame;
		
	}
	//LIBERAR MEMORIA	
	render_clean();	
	return 0;
}


void grabar_imagen(void)
{
	int i;
	FILE *file = fopen("imagen.ppm","w");
	
	fprintf(file,"%s\n","P3");
	fprintf(file,"%d %d\n",estadosrender.ven_width,estadosrender.ven_height);
	fprintf(file,"%d\n",255);
	for(i = 0; i<estadosrender.ven_width*estadosrender.ven_height ; i++)
	{
		Color pixel = {estadosrender.color_buffer[i]};
		fprintf(file,"%d %d %d\n",pixel.rgba.r,pixel.rgba.g,pixel.rgba.b);
	}
	
	fclose(file);
}


void render_init(void)
{
	
	//Crear ventana
	SDL_CreateWindowAndRenderer("Motor GPU",estadosrender.ven_width, estadosrender.ven_height, SDL_WINDOW_OPENGL,&ventana,&(estadosrender.renderer));	
	assert(ventana && "No se pudo crear la ventana\n");
	assert(estadosrender.renderer && "No se pudo crear el renderer\n");
	
	estadosrender.color_buffer = malloc( estadosrender.ven_width * estadosrender.ven_height * sizeof(uint32_t));	
	assert(estadosrender.color_buffer && "No se pudo crear el color buffer\n");
	
	estadosrender.textura = SDL_CreateTexture(estadosrender.renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING,estadosrender.ven_width,estadosrender.ven_height);	
	assert(estadosrender.textura && "No se pudo crear la textura\n");

}

void render_clean(void)
{	
	//LIBERAR MEMORIA
	free_array(estadosrender.figuras_buffer);
	SDL_DestroyTexture(estadosrender.textura);
	SDL_DestroyRenderer(estadosrender.renderer);
	SDL_DestroyWindow(ventana);	
	free(estadosrender.color_buffer);
}

