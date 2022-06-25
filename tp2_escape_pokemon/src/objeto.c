#include "objeto.h"
#include "estructuras.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHARS_BOOL 6

int string_a_bool(char *string)
{
	if(strcmp(string, "true") == 0) {
		return 1;
	} else if(strcmp(string, "false") == 0) {
		return 0;
	}

	return -1;
}

struct objeto *objeto_crear_desde_string(const char *string)
{
	if(string == NULL || strcmp(string, "") == 0)
		return NULL;

	struct objeto *objeto = malloc(sizeof(struct objeto));

	if(objeto == NULL)
		return NULL;

	char flag[MAX_CHARS_BOOL];
	int cantidad_leidos = sscanf(string, "%[^;];%[^;];%5s[^\n]\n", objeto->nombre, objeto->descripcion, flag);

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