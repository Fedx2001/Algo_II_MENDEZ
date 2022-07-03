#ifndef ESCAPE_H_
#define ESCAPE_H_

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "sala.h"

#define ERROR_EJECUCION -1
#define BUFFER_ENTRADA 1024
#define LIMPIAR_PANTALLA "\033[1;1H\033[2J"
#define BLANCO "\x1b[37;1m"
#define VERDE "\x1b[32;1m"
#define ROJO "\x1b[31;1m"
#define AMARILLO "\x1b[33;1m"
#define NORMAL "\x1b[0m"
#define SALIR "salir"
#define AYUDA "ayuda"
#define AGARRAR "agarrar"
#define DESCRIBIR "describir"
#define CANTIDAD_OBJETIVOS 3
#define POSISCION_VERBO 0
#define POSISCION_OBJETO1 1
#define POSISCION_OBJETO2 2

/*
 * Toma un string y lo pasa a minúsculas in-place.
 *
 * Devuelve un puntero a la primera posición del string actualizado o NULL en caso de error.
 */
char *en_minusculas(char *string);

/*
 * Muestra por consola una introducción al juego y el concepto del mismo al comenzar a jugar.
 */
void mostrar_intro();

/*
 * Muestra por consola todos los comandos estándar disponibles y la documentación 
 * correspondiente a cada uno.
 */
void mostrar_ayuda();

/*
 * Muestra un mensaje(con macros que definitivamente no me robe de pa2mm.h!)
 * según el tipo de acción correspondiente a la interaccion ejecutada.
 * 
 * aux PUEDE ser NULL.
 */
void mostrar_mensaje(const char *mensaje, enum tipo_accion accion, void *aux);

/*
 * Toma un vector de punteros a char y libera el espacio reservado por el mismo.
 *
 * Si el vector es nulo o no se pasa una cantidad mayor a 0, no hace nada.
 */
void liberar_vector(char **vector, size_t tamanio);

/*
 * Recibe una sala, un verbo y dos objetos(el objeto_parametro puede ser nulo)
 * y ejecuta la interaccion con el verbo y los objetos correspondientes de la sala.
 * 
 * Si la sala es nula no hace nada.
 */
void ejecutar_interaccion_con_palabras(sala_t *sala, char *verbo, char *objeto, char *objeto_parametro);

/*
 * Recibe una sala, y pide al usuario que ingrese un texto con el formato 'verbo objeto1 objeto2'.
 * Dicho texto luego se procesa para extraer los strings necesarios para ejecutar una interaccion de la sala.
 * 
 * Devuelve false siempre que se ejecuta y true en caso de que el usuario quiera salir del programa.
 */
bool pedir_y_procesar_entrada(sala_t *sala);

/*
 * Muestra los objetos conocidos y poseidos de una sala pasada por parametro.
 *
 * Si la sala es nula no hace nada.
 */
void mostrar_objetos(sala_t *sala);

#endif