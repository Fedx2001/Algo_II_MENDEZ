#include "lectura_archivos.h"

struct objeto **leer_objetos_de_archivo(FILE *f_objetos, int *cantidad_objetos)
{
	char buffer[MAX_LECTURA];
	char *linea = fgets(buffer, MAX_LECTURA, f_objetos);

	struct objeto **objetos;

	struct objeto **bloque;

	objetos = malloc(sizeof(struct objeto *));
	if(!objetos)
		return NULL;

	while(linea) {
		unsigned int cantidad_aux = (unsigned int)*cantidad_objetos;

		bloque = realloc(objetos, (cantidad_aux+1) * sizeof(struct objeto *));
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
/*
struct interaccion **leer_interacciones_de_archivo(FILE *f_interacciones, int *cantidad_interacciones)
{
	char buffer[MAX_LECTURA];
	char *linea = fgets(buffer, MAX_LECTURA, f_interacciones);

	struct objeto **interacciones;

	struct objeto **bloque;

	interacciones = malloc(sizeof(struct objeto *));
	if(!interacciones)
		return NULL;

	while(linea) {
		unsigned int cantidad_aux = (unsigned int)*cantidad_interacciones;

		bloque = realloc(interacciones, (cantidad_aux+1) * sizeof(struct objeto *));
		if(!bloque) {
			return NULL;
		}

		interacciones = bloque;

		struct interaccion *interaccion_actual = interaccion_crear_desde_string(linea);
		if(!interaccion_actual) {
			return NULL;
		}

		interacciones[*cantidad_interacciones] = interaccion_actual;

		(*cantidad_interacciones)++;

		linea = fgets(buffer, MAX_LECTURA, f_interacciones);
	}

	return interacciones;
}
*/