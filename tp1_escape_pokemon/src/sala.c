#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_LECTURA 1024

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	sala_t *sala = malloc(sizeof(sala_t));
	if(!sala)
		return NULL;
	
	sala->cantidad_objetos = 0;
	sala->cantidad_interacciones = 0;

	FILE *f_objetos = fopen(objetos, "r");

	if(!f_objetos) {
		return sala;
	}

	char buffer[MAX_LECTURA];
	char *linea = fgets(buffer, MAX_LECTURA, f_objetos);
	struct objeto **bloque = malloc(sizeof(struct objeto *));
	if(!bloque) {
		fclose(f_objetos);
		return sala;
	}
	sala->objetos = bloque;

	while(linea) {
		struct objeto *vector_objetos = realloc(vector_objetos, (sala->cantidad_objetos+1) * sizeof(struct objeto));
		
		

		linea = fgets(buffer, MAX_LECTURA, f_objetos);
	}

	fclose(f_objetos);

	for(int i = 0; i < sala->cantidad_objetos; i++) {
		printf("%s\n", sala->objetos[i]->nombre);
	}
	// FILE *f_interacciones = fopen(interacciones, "r");
	// if(!f_interacciones)
	// 	return NULL;

	// fclose(f_interacciones);
	
	return sala;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	return NULL;
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,
				const char *objeto2)
{
	return false;
}

void sala_destruir(sala_t *sala)
{
	if(!sala) 
		return;
	
	if(sala->objetos) 
		for(int i = 0; i < sala->cantidad_objetos; i++) {
			free(sala->objetos[i]);
		}

	free(sala->objetos);

	// if(sala->interacciones) 
	// 	for(int i = sala->cantidad_interacciones; i > 0; i--) {
	// 		free(sala->interacciones[--i]);
	// 	}

	// free(sala->interacciones);
	
	free(sala);
}
