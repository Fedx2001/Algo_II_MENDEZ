#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "hash.h"
#include "menu_juego.h"

struct comando{
	const char* nombre;
	const char* documentacion;
};

struct menu{
	hash_t *comandos;
};

comando_t *comando_crear(const char* nombre, const char* info)
{
	comando_t *comando = calloc(1, sizeof(comando_t));

	comando->nombre = nombre;
	comando->documentacion = info;

	return comando;
}

menu_t *menu_crear()
{
	menu_t *menu = calloc(1, sizeof(menu_t));
	menu->comandos = hash_crear(10);
	return menu;
}

void agregar_comando(menu_t *menu, const char *nombre, const char *doc)
{
	comando_t *comando = comando_crear(nombre, doc);
	
	hash_insertar(menu->comandos, nombre, comando, NULL);
}

/*void menu_ejecutar(menu_t *menu, void* contexto){
	char buffer[512];
	buffer[0] = 0;

	while(!juego->finalizado){
		printf("> ");
		char* linea  = leer_linea(buffer, 512);

		if(linea){
			comando_t *comando = hash_buscar(menu->comandos, linea);
			if(comando){
				comando->ejecutar(linea, contexto);
			}
			else{
				printf("No sé como hacer eso");
			}
		}
		printf("\n");
	}
}*/

bool mostrar_comando(const char *nombre, void *comando, void *aux)
{
	comando_t *comando_actual = comando;
	printf("> %s \t %s \n", comando_actual->nombre, comando_actual->documentacion);

	return true;
}

void mostrar_ayuda(menu_t *menu)
{
	printf("\n> COMANDOS DISPONIBLES <\n");

	hash_con_cada_clave(menu->comandos, mostrar_comando, NULL);

	printf("\n");
}