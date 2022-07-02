#ifndef BUBBLESORT_H_
#define BUBBLESORT_H_

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
 * Ordena un vector (in-place) que contiene elementos
 * de cualquier tipo utilizando el comparador pasado por parámetro.
 * 
 * Si el vector es NULL, el comparador es NULL, o no se pasan
 * los tamaños requeridos, no hace nada.
 */
void bubblesort_strings(char **vector, size_t tope);

#endif