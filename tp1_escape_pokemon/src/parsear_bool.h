#ifndef PARSEAR_BOOL_H_
#define PARSEAR_BOOL_H_

#include <stdbool.h>

/*
 * Dada una cadena, deuvelve el valor correspondiente a booleano (en formato de entero, es decir 0 o 1)
 * o -1 si no es una cadena interpretable como bool.
 */
int string_a_bool(char *string);

/*
 * Recibe un flag booleano y devuelve un texto indicando si es válido o no.
 *
 * Resulta valido si el flag es true, e invalido si el flag es false.
 */
char *pasear_bool_a_texto(bool flag);

#endif