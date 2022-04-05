#include "lectura_archivos.h"

struct objeto **leer_objetos_de_archivo(FILE *f_objetos, int *cantidad_objetos)
{
	char buffer[MAX_LECTURA];
	char *linea = fgets(buffer, MAX_LECTURA, f_objetos);

	struct objeto **objetos = NULL;

	struct objeto **bloque = NULL;

	while(linea) {
		bloque = realloc(objetos, ((unsigned)*cantidad_objetos+1) * sizeof(struct objeto *));
		if(!bloque)
			return NULL;

		objetos = bloque;

		struct objeto *objeto_actual = objeto_crear_desde_string(linea);
		if(!objeto_actual) {
			free(objetos);
			return NULL;
		}

		objetos[*cantidad_objetos] = objeto_actual;

		(*cantidad_objetos)++;

		linea = fgets(buffer, MAX_LECTURA, f_objetos);
	}

	return objetos;
}

struct interaccion **leer_interacciones_de_archivo(FILE *f_interacciones, int *cantidad_interacciones)
{
	char buffer[MAX_LECTURA];
	char *linea = fgets(buffer, MAX_LECTURA, f_interacciones);

	struct interaccion **interacciones = NULL;

	struct interaccion **bloque = NULL;

	while(linea) {
		bloque = realloc(interacciones, ((unsigned)*cantidad_interacciones+1) * sizeof(struct objeto *));
		if(!bloque)
			return NULL;

		interacciones = bloque;

		struct interaccion *interaccion_actual = interaccion_crear_desde_string(linea);

		if(!interaccion_actual) {
			free(interacciones);
			return NULL;
		}

		interacciones[*cantidad_interacciones] = interaccion_actual;

		(*cantidad_interacciones)++;

		linea = fgets(buffer, MAX_LECTURA, f_interacciones);
	}

	return interacciones;
}