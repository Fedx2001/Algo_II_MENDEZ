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

	/*
	LECTURA OBJETOS
	*/
	FILE *f_objetos = fopen(objetos, "r");

	if(!f_objetos) {
		return sala;
	}

	char buffer[MAX_LECTURA];
	char *linea = fgets(buffer, MAX_LECTURA, f_objetos);
	struct objeto **bloque_objetos;

	sala->objetos = malloc(sizeof(struct objeto *));
	if(!sala->objetos)
		return sala;

	while(linea) {
		unsigned int cantidad_objetos = (unsigned int)sala->cantidad_objetos;

		bloque_objetos = realloc(sala->objetos, (cantidad_objetos+1) * sizeof(struct objeto *));
		if(!bloque_objetos) {
			fclose(f_objetos);
			return sala;
		}
		sala->objetos = bloque_objetos;

		struct objeto *objeto_actual = objeto_crear_desde_string(linea);
		if(!objeto_actual) {
			fclose(f_objetos);
			return sala;
		}
		
		sala->cantidad_objetos++;

		sala->objetos[cantidad_objetos] = objeto_actual;

		linea = fgets(buffer, MAX_LECTURA, f_objetos);
	}

	fclose(f_objetos);

	/*
	LECTURA INTERACCIONES
	*/
	FILE *f_interacciones = fopen(interacciones, "r");
	
	if(!f_interacciones)
		return sala;

	linea = fgets(buffer, MAX_LECTURA, f_interacciones);
	// struct interaccion **bloque_interacciones;

	sala->interacciones = malloc(sizeof(struct interaccion *));
	if(!sala->interacciones)
		return sala;

	// while(linea) {
	// 	unsigned int cantidad_objetos = (unsigned int)sala->cantidad_objetos;

	// 	bloque_interacciones = realloc(sala->interacciones, (cantidad_interacciones+1) * sizeof(struct interaccion *));
	// 	if(!bloque_interacciones) {
	// 		fclose(f_interacciones);
	// 		return sala;
	// 	}
	// 	sala->interacciones = bloque_interacciones;

	// 	struct interaccion *interaccion_actual = interaccion_crear_desde_string(linea);
	// 	if(!interaccion_actual) {
	// 		fclose(f_interacciones);
	// 		return sala;
	// 	}
		
	// 	sala->cantidad_interacciones++;

	// 	sala->interacciones[cantidad_interacciones] = interaccion_actual;

	//	linea = fgets(buffer, MAX_LECTURA, f_interacciones);
	// }

	fclose(f_interacciones);
	
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
	
	if(sala->objetos) {
		for(int i = 0; i < sala->cantidad_objetos; i++) {
			free(sala->objetos[i]);
		}

		free(sala->objetos);
	}

	if(sala->interacciones) {
		for(int i = sala->cantidad_interacciones; i > 0; i--) {
			free(sala->interacciones[--i]);
		}

		free(sala->interacciones);
	}
	
	free(sala);
}
