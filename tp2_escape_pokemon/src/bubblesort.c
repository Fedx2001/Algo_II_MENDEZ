#include "bubblesort.h"

void bubblesort_strings(char **vector, size_t tope)
{
	if(!vector || tope == 0) 
		return;

	for(size_t i = 0; i < tope; i++){
		for(size_t j = 0; j < tope-i-1; j++){
			if(strcmp(vector[j], vector[j+1]) > 0) {
				char *aux = vector[j];
				vector[j] = vector[j+1];
				vector[j+1] = aux;
			}
		}
	}
}