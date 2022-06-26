#include "interaccion.h"
#include "estructuras.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct interaccion *interaccion_crear_desde_string(const char *string)
{
	if(string == NULL || strcmp(string, "") == 0) return NULL;

	struct interaccion *interaccion = calloc(1, sizeof(struct interaccion));
	struct accion accion = {ACCION_INVALIDA, "", ""};
	
	if(interaccion == NULL) return NULL;

	int leidos_interacc = sscanf(string, "%[^;];%[^;];%[^;];%*[^\n]\n", interaccion->objeto, interaccion->verbo, interaccion->objeto_parametro);
	if(strcmp(interaccion->objeto_parametro, "_") == 0) strcpy(interaccion->objeto_parametro, "");
	
	char tipo = 0;
	int leidos_accion = sscanf(string, "%*[^;];%*[^;];%*[^;];%c:%[^:]:%[^\n]\n", &tipo, accion.objeto, accion.mensaje);

	if(leidos_interacc != 3 || leidos_accion != 3) {
		free(interaccion);
		return NULL;
	}

	if(strcmp(accion.objeto, "_") == 0) strcpy(accion.objeto, "");

	switch(tipo) {
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
	case 'g':
		accion.tipo = ESCAPAR;
		break;
	default:
		accion.tipo = ACCION_INVALIDA;
		break;
	}

	interaccion->accion = accion;

	return interaccion;
}
