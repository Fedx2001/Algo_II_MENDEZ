#include "src/sala.h"
#include "src/parsear_bool.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Recibe un puntero a un vector de nombres de objetos y la cantidad
 * de objetos que tiene, y muestra los nombres de los objetos.
 *
 * Si el vector es nulo, no hace nada.
 */
void mostrar_nombres_objetos(char **nombres, int *cantidad)
{
	if(cantidad != NULL && *cantidad == -1)
		return;

	for(int i = 0; i < *cantidad; i++) {
		printf("%i: %s\n", i, nombres[i]);
	}
}

int main(int argc, char *argv[])
{
	//Los archivos deben venir como parámetros del main
	if(argc != 3)
		return -1;

	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);
	if(sala != NULL) {
		//Mostrar todos los objetos en la sala
		int cantidad = 0;
		char **nombres_objetos = sala_obtener_nombre_objetos(sala, &cantidad);
		printf("Objetos...\n");
		mostrar_nombres_objetos(nombres_objetos, &cantidad);
		printf("\n");

		//Mostrar si son válidas las siguientes interacciones
		//1. examinar habitacion
		//2. abrir pokebola
		//3. usar llave cajon
		//4. quemar mesa
		printf("Interacciones...\n");
		bool es_valida;

		es_valida = sala_es_interaccion_valida(sala, "examinar", "habitacion", "");
		printf("Examinar la habitacion: %s\n", pasear_bool_a_texto(es_valida));
		es_valida = sala_es_interaccion_valida(sala, "abrir", "pokebola", "_");
		printf("Abrir pokebola: %s\n", pasear_bool_a_texto(es_valida));
		es_valida = sala_es_interaccion_valida(sala, "usar", "llave", "cajon");
		printf("Usar llave en el cajon: %s\n", pasear_bool_a_texto(es_valida));
		es_valida = sala_es_interaccion_valida(sala, "quemar", "mesa", "");
		printf("Quemar la mesa: %s\n", pasear_bool_a_texto(es_valida));

		if(nombres_objetos != NULL)
			free(nombres_objetos);

		sala_destruir(sala);
	}
	return 0;
}