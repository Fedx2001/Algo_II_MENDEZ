#ifndef	LIBERAR_MEMORIA_H_
#define LIBERAR_MEMORIA_H_

#include "estructuras.h"

/*
 * Recibe un vector de punteros a objetos reservado dinamicamente,
 * junto con la cantidad de objetos que tiene, y libera toda la memoria reservada. 
 */
void liberar_objetos(struct objeto **objetos, int cant_objetos);

/*
 * Recibe un vector de punteros a interacciones reservado dinamicamente,
 * junto con la cantidad de interacciones que tiene, y libera toda la memoria reservada. 
 */
void liberar_interacciones(struct interaccion **interacciones, int cant_interacc);

#endif