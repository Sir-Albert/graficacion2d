cflags = -Wall -Werror -pedantic -std=c99 -O2
dflags = -Wall -Werror -pedantic -std=c99 -g
sdl_include = -I deps/SDL3-3.2.20/i686-w64-mingw32/include 
sdl_lib = -L deps/SDL3-3.2.20/i686-w64-mingw32/lib -lSDL3 
estruct_include = -I src/estructuras
estruct_lib = -L deps -lPila -lLista 
source = $(wildcard src/*.c) $(wildcard src/**/*.c)
output = bin/render_cpu

build :
	gcc $(cflags) $(source) -o $(output) $(sdl_include) $(sdl_lib) $(estruct_include) $(estruct_lib)
	copy "deps\SDL3-3.2.20\i686-w64-mingw32\bin\SDL3.dll" "bin\SDL3.dll"
	@echo "Compilo Exitosamente!!!"
rebuild:
	make -C src\estructuras\nodos
	make -C src\estructuras\pila
	make -C src\estructuras\pila
	gcc $(cflags) $(source) -o $(output) $(sdl_include) $(sdl_lib) $(estruct_include) $(estruct_lib)
	copy "deps\SDL3-3.2.20\i686-w64-mingw32\bin\SDL3.dll" "bin\SDL3.dll"
	@echo "Compilo Exitosamente!!!"
debug:
	gcc $(dflags) $(source) -o $(output) -I $(sdl_include) -L $(sdl_lib)
	gdb --se $(output)
run :
	bin\render_cpu.exe