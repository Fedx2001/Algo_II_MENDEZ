#include "lectura_archivos.h"
#include "estructuras.h"
#include "objeto.h"
#include "interaccion.h"
#include "liberar_memoria.h"

struct objeto **leer_objetos_de_archivo(FILE *f_objetos, int *cant_objetos)
{
	char buffer[MAX_LECTURA];
	char *linea = fgets(buffer, MAX_LECTURA, f_objetos);

	struct objeto **objetos = NULL;

	struct objeto **bloque = NULL;

	while(linea) {
		bloque = realloc(objetos, ((unsigned)*cant_objetos+1) * sizeof(struct objeto *));
		if(bloque == NULL)
			return NULL;

		objetos = bloque;

		struct objeto *objeto_actual = objeto_crear_desde_string(linea);
		if(objeto_actual == NULL) {
			liberar_objetos(objetos, *cant_objetos);
			return NULL;
		}

		objetos[*cant_objetos] = objeto_actual;

		(*cant_objetos)++;

		linea = fgets(buffer, MAX_LECTURA, f_objetos);
	}

	return objetos;
}

struct interaccion **leer_interacciones_de_archivo(FILE *f_interacciones, int *cant_interacc)
{
	char buffer[MAX_LECTURA];
	char *linea = fgets(buffer, MAX_LECTURA, f_interacciones);

	struct interaccion **interacciones = NULL;

	struct interaccion **bloque = NULL;

	while(linea) {
		bloque = realloc(interacciones, ((unsigned)*cant_interacc+1) * sizeof(struct objeto *));
		if(bloque == NULL)
			return NULL;

		interacciones = bloque;

		struct interaccion *interaccion_actual = interaccion_crear_desde_string(linea);

		if(interaccion_actual == NULL) {
			liberar_interacciones(interacciones, *cant_interacc);
			return NULL;
		}

		interacciones[*cant_interacc] = interaccion_actual;

		(*cant_interacc)++;

		linea = fgets(buffer, MAX_LECTURA, f_interacciones);
	}

	return interacciones;
}