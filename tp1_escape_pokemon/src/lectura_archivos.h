#ifndef LECTURA_ARCHIVOS_H_
#define LECTURA_ARCHIVOS_H_

#include "estructuras.h"
#include "objeto.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LECTURA 1024

/*
 * Dado un archivo con objetos, devuelve un puntero a un vector de objetos.
 *
 * En caso de error devuelve NULL.
 */
struct objeto **leer_objetos_de_archivo(FILE *f_objetos, int *cantidad_objetos);

/*
 * Dado un archivo con interacciones, devuelve un puntero a un vector de interacciones.
 *
 * En caso de error devuelve NULL.
 */
struct interaccion **leer_interacciones_de_archivo(FILE *f_interacciones, int *cantidad_interacciones);

#endif