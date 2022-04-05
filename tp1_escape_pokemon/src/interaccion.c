#include "estructuras.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>

#define FORMATO_INTERACCION "%[^;];%[^;];%[^;];%*[^:]:%*[^:]:%*[^\n]\n"
#define FORMATO_ACCION "%*[^;];%*[^;];%*[^;];%[^:]:%[^:]:%[^\n]\n"
#define MAX_LINEA 1024
#define MAX_TIPO 2

struct interaccion *interaccion_crear_desde_string(const char *string)
{
	struct interaccion *interaccion = malloc(sizeof(struct interaccion));
	struct accion accion;
	if(interaccion == NULL)
		return NULL;

	int leidos_interacc = sscanf(string, FORMATO_INTERACCION, interaccion->objeto, interaccion->verbo, interaccion->objeto_parametro);
	char str_tipo[MAX_TIPO];
	int leidos_accion = sscanf(string, FORMATO_ACCION, str_tipo, accion.objeto, accion.mensaje);

	if(leidos_interacc != 3 || leidos_accion != 3) {
		free(interaccion);
		return NULL;
	}

	char tipo_acc = str_tipo[0];

	switch(tipo_acc) {
	case 'd':
		accion.tipo = DESCUBRIR_OBJETO;
		break;
	case 'r':
		accion.tipo = REEMPLAZAR_OBJETO;
		break;
	case 'e':
		accion.tipo = ELIMINAR_OBJETO;
		break;
	case 'm':
		accion.tipo = MOSTRAR_MENSAJE;
		break;
	default:
		accion.tipo = ACCION_INVALIDA;
		break;
	}

	interaccion->accion = accion;

	return interaccion;
}
