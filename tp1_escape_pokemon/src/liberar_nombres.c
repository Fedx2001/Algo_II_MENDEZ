#include "liberar_nombres.h"
#include <stdlib.h>

void liberar_nombres(char **nombres, int *cant_nombres)
{
	if(nombres == NULL)
		return;
	
	if(cant_nombres != NULL) {
		for(int i = 0; i < *cant_nombres; i++) {
			free(nombres[i]);
		}
		free(cant_nombres);
	}
	
	free(nombres);
}