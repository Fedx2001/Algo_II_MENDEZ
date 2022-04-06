#ifndef LECTURA_ARCHIVOS_H_
#define LECTURA_ARCHIVOS_H_
#include <stdlib.h>
#include <stdio.h>

#define MAX_LECTURA 1024

/*
 * Dado un archivo con objetos, devuelve un puntero a un vector dinamico de objetos
 * reservado con Malloc.
 * En caso de error devuelve NULL.
 * 
 * El vector debe ser liberado con free.
 */
struct objeto **leer_objetos_de_archivo(FILE *f_objetos, int *cantidad_objetos);

/*
 * Dado un archivo con interacciones, devuelve un puntero a un vector dinamico de interacciones
 * reservado con Malloc.
 * En caso de error devuelve NULL.
 * 
 * El vector debe ser liberado con free.
*/
struct interaccion **leer_interacciones_de_archivo(FILE *f_interacciones, int *cantidad_interacciones);

#endif