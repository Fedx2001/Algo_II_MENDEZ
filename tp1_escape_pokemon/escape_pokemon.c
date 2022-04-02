#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	//Los archivos deben venir como parámetros del main
	if(argc != 3) {
		printf("Numero de parametros invalido!\n");
		return -1;
	}

	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);

	if (sala == NULL) {
		printf("Error al crear la sala de escape\n");
		return -1;
	}

	//Mostrar todos los objetos en la sala

	printf("Objetos...\n");

	//Mostrar si son válidas las siguientes interacciones
	//1. examinar habitacion
	//2. abrir pokebola
	//3. usar llave cajon
	//4. quemar mesa

	printf("Interacciones...\n");

	sala_destruir(sala);

	return 0;
}
