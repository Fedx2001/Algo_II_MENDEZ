#ifndef __FUNCIONES_AUXILIARES_H__
#define __FUNCIONES_AUXILIARES_H__

#include "sala.h"

/*
 * Recibe un nombre de objeto, un objeto y un contenedor con un vector y la cantidad
 * de elementos del mismo, e inserta los nombres de objetos de un hash en el vector
 * del contenedor.
*/
bool agregar_nombres_en_vector(const char *nombre_objeto, void *objeto, void *contenedor);

/*
 * Recibe dos interacciones, compara sus objetos y verbos y 
 * devuelve 0 si la interaccion pasada como segundo parametro tiene 
 * los mismos objetos y verbos que la interaccion pasada como primer parametro.
 * 
 * Devuelve -1 en caso contrario o si se produce algun error.
 */
int comparar_interacciones(void *interaccion_comparada, void *interaccion_a_comparar);

/*
 * Recibe una interaccion y realiza la accion correspondiente a la interaccion si
 * no fue realizada previamente.
 * 
 * Si la accion de la interaccion es invalida, no hace nada.
 * 
 * Si la interaccion se ejecutó correctamente, incrementa la cantidad de interacciones ejecutadas.
 */
void ejecutar_interaccion(sala_t *sala, struct interaccion *a_ejecutar, int *cantidad_ejecutadas, 
			  void (*mostrar_mensaje)(const char *mensaje,
						  enum tipo_accion accion,
						  void *aux),
			  void *aux);

#endif