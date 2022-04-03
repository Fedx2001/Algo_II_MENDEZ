#include "objeto.h"
#include "estructuras.h"
#include "verificar_bool.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FORMATO "%[^;];%[^;];%[^\n]\n"
#define MAX_CHARS_BOOL 5

struct objeto *objeto_crear_desde_string(const char *string)
{
	struct objeto *objeto = malloc(sizeof(struct objeto));

	if(!objeto)
		return NULL;
	
	char booleano[MAX_CHARS_BOOL];
	int cantidad_leidos = sscanf(string, FORMATO, objeto->nombre, objeto->descripcion, booleano);

	if(cantidad_leidos != 3) {
		free(objeto);
		return NULL;
	}
	
	int es_asible = verificar_bool(booleano);

	if(es_asible == -1) {
		free(objeto);
		return NULL;
	}

	objeto->es_asible = (bool)es_asible;

	return objeto;
}