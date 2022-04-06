#include "liberar_memoria.h"
#include <stdlib.h>
#include <stdio.h>

void liberar_objetos(struct objeto **objetos, int *cant_objetos)
{
	if(objetos == NULL)
		return;

	for(int i = 0; i < *cant_objetos; i++) {
		free(objetos[i]);
	}

	free(objetos);

	(*cant_objetos) = 0;
}

void liberar_interacciones(struct interaccion **interacciones, int *cant_interacc)
{
	if(interacciones == NULL)
		return;

	for(int i = 0; i < *cant_interacc; i++) {
		free(interacciones[i]);
	}

	free(interacciones);

	(*cant_interacc) = 0;
}
