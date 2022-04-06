#include "objeto.h"
#include "estructuras.h"
#include "string_a_bool.h"
#include <stdlib.h>
#include <stdio.h>

#define FORMATO_OBJETO "%[^;];%[^;];%[^\n]\n"
#define MAX_CHARS_BOOL 5

struct objeto *objeto_crear_desde_string(const char *string)
{
	struct objeto *objeto = malloc(sizeof(struct objeto));

	if(objeto == NULL || string == NULL)
		return NULL;

	char flag[MAX_CHARS_BOOL];
	int cantidad_leidos = sscanf(string, FORMATO_OBJETO, objeto->nombre, objeto->descripcion, flag);

	if(cantidad_leidos != 3) {
		free(objeto);
		return NULL;
	}

	int es_asible = string_a_bool(flag);

	if(es_asible == -1) {
		free(objeto);
		return NULL;
	}

	objeto->es_asible = (bool)es_asible;

	return objeto;
}