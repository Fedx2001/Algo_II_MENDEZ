#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"
#include "lectura_archivos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	sala_t *sala = malloc(sizeof(sala_t));
	if(sala == NULL)
		return NULL;

	sala->cantidad_objetos = 0;
	sala->cantidad_interacciones = 0;

	FILE *f_objetos = fopen(objetos, "r");

	if(f_objetos == NULL)
		return sala;

	sala->objetos = leer_objetos_de_archivo(f_objetos, &(sala->cantidad_objetos));
	fclose(f_objetos);

	if(sala->objetos == NULL)
		return sala;

	FILE *f_interacciones = fopen(interacciones, "r");

	if(f_interacciones == NULL)
		return sala;

	sala->interacciones = leer_interacciones_de_archivo(f_interacciones, &(sala->cantidad_interacciones));
	fclose(f_interacciones);

	if(sala->interacciones == NULL)
		return sala;

	return sala;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if(sala == NULL || sala->objetos == NULL || sala->cantidad_objetos <= 0) {
		*cantidad = -1;
		return NULL;
	}

	char **nombres_objs = malloc((unsigned int)sala->cantidad_objetos * sizeof(char *));
	if(nombres_objs == NULL) {
		*cantidad = -1;
		return NULL;
	}

	char *bloque;

	for(int i = 0; i < sala->cantidad_objetos; i++) {
		bloque = malloc((strlen(sala->objetos[i]->nombre)+1) * sizeof(char));
		if(bloque == NULL) {
			*cantidad = -1;
			break;
		}
		nombres_objs[i] = bloque;

		strcpy(nombres_objs[i], sala->objetos[i]->nombre);
		(*cantidad)++;
	}

	return nombres_objs;
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,
				const char *objeto2)
{
	for(int i = 0; i < sala->cantidad_interacciones; i++) {
		int cmp_verbo = strcmp(sala->interacciones[i]->verbo, verbo);
		int cmp_objeto1 = strcmp(sala->interacciones[i]->objeto, objeto1);
		int cmp_objeto2;
		if(strcmp(objeto2, "") == 0){
			cmp_objeto2 = strcmp(sala->interacciones[i]->objeto_parametro, "_");
		} else {
			cmp_objeto2 = strcmp(sala->interacciones[i]->objeto_parametro, objeto2);
		}

		if(cmp_verbo == 0 && cmp_objeto1 == 0 && cmp_objeto2 == 0)
			return true;
	}
	return false;
}

void sala_destruir(sala_t *sala)
{
	if(sala == NULL)
		return;

	if(sala->objetos != NULL) {
		for(int i = 0; i < sala->cantidad_objetos; i++) {
			free(sala->objetos[i]);
		}
		free(sala->objetos);
	}

	if(sala->interacciones != NULL) {
		for(int i = 0; i < sala->cantidad_interacciones; i++) {
			free(sala->interacciones[i]);
		}
		free(sala->interacciones);
	}

	free(sala);
}
