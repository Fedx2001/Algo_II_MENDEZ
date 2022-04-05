#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define MAX_TEXTO 9

/*
 * Recibe un puntero a un vector de nombres de objetos y la cantidad
 * de objetos que tiene, y muestra los nombres de los objetos.
 *
 * Si el vector es nulo, no hace nada.
 */
void mostrar_nombres_objetos(char **nombres, int cantidad)
{
	if(nombres == NULL)
		return;

	for(int i = 0; i < cantidad; i++) {
		printf("%i: %s\n", i, nombres[i]);
	}
}

/*
 * Recibe un puntero a un vector de nombres de objetos y la cantidad
 * de objetos que tiene, destruyendolo y liberando toda la memoria reservada
 * para el mismo.
 *
 * Si el vector es nulo, no hace nada.
 */
void liberar_vector_nombres(char **nombres, int cantidad)
{
	if(nombres == NULL)
		return;

	for(int i = 0; i < cantidad; i++) {
		free(nombres[i]);
	}

	free(nombres);
}

/*
 * Recibe un flag booleano y devuelve un texto indicando si es válido o no.
 *
 * Resulta valido si el flag true, e invalido si el flag es false.
 */
char *es_valido_texto(bool flag)
{
	return (flag ? "Válido" : "Inválido");
}

int main(int argc, char *argv[])
{
	//Los archivos deben venir como parámetros del main
	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);
	if(argc != 3 || sala == NULL)
		return ERROR;

	//Mostrar todos los objetos en la sala
	printf("Objetos...\n");
	int cantidad = 0;
	char **nombres_objetos = sala_obtener_nombre_objetos(sala, &cantidad);

	mostrar_nombres_objetos(nombres_objetos, cantidad);
	liberar_vector_nombres(nombres_objetos, cantidad);

	printf("\n");

	//Mostrar si son válidas las siguientes interacciones
	//1. examinar habitacion
	//2. abrir pokebola
	//3. usar llave cajon
	//4. quemar mesa
	printf("Interacciones...\n");
	bool interaccion_es_valida;

	interaccion_es_valida = sala_es_interaccion_valida(sala, "examinar", "habitacion", "");
	printf("Examinar la habitacion: %s\n", es_valido_texto(interaccion_es_valida));

	interaccion_es_valida = sala_es_interaccion_valida(sala, "abrir", "pokebola", "_");
	printf("Abrir pokebola: %s\n", es_valido_texto(interaccion_es_valida));

	interaccion_es_valida = sala_es_interaccion_valida(sala, "usar", "llave", "cajon");
	printf("Usar llave en el cajon: %s\n", es_valido_texto(interaccion_es_valida));

	interaccion_es_valida = sala_es_interaccion_valida(sala, "quemar", "mesa", "");
	printf("Quemar la mesa: %s\n", es_valido_texto(interaccion_es_valida));

	sala_destruir(sala);

	return 0;
}