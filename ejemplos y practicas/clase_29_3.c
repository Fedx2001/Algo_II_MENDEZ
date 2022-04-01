#include <stdio.h>
#include <stdlib.h>

/*
 * Ejemplo de int pointer
 */
// int main(int argc, char *argv[])
// {
// 	int numero = 5;
// 	printf("El número es %i\n", numero);
// 	int *puntero = &numero;
// 	printf("El puntero apunta al valor %i\n", *puntero);
// 	printf("El puntero apunta a la direccion de memoria %p\n", puntero);
// 	*puntero = 6;
// 	printf("El puntero apunta al valor %i\n", *puntero);
//	return 0;
// }

/*
 * PUNTERO DOBLE
 */
// int main(int argc, char *argv[])
// {
// 	int numero = 5;
	
// 	int *puntero1 = &numero;
// 	int **puntero2 = &puntero1;

// 	printf("Puntero1 almacena el valor %p\n", puntero1);
// 	printf("Puntero2 almacena el valor %p\n", puntero2);
// 	printf("*puntero2 es %p\n", *puntero2);
// 	printf("**puntero2 es %i\n", **puntero2);
//
//	return 0;
// }

/*
 * Aritmetica de Punteros y casteos
 */
// int main(int argc, char *argv[])
// {
// 	char vector_numeros[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

// 	char *chars = vector_numeros;

// 	int *ints = (int *)chars;

// 	printf("El primer char es %i\n", chars[0]);
// 	printf("El primer int es 0x%.8x\n", ints[0]);

// 	printf("El segundo char es %i\n", chars[1]);
// 	printf("El segundo int es 0x%.8x\n", ints[1]);

// 	return 0;
// }


void agregar_numero(int **vector, int *tamanio, int numero)
{
	int *bloque = realloc(*vector, ((*tamanio)+1) * sizeof(int)); // o sizeof(int) en este caso, pero esto es segun Kernel Linux

	if(bloque == NULL)
		return;

	bloque[*tamanio] = numero;
	(*tamanio)++;

	*vector = bloque;
}

// void agregar_numero0(int **vector, int *tamanio, int numero)
// {
// 	int *bloque=NULL;

// 	if(tamanio == 0) {
// 		bloque = malloc(sizeof(int));
// 	} else {
// 		bloque = realloc(*vector, ((*tamanio)+1) * sizeof(int));
// 	}

// 	if(bloque == NULL)
// 		return;

// 	bloque[*tamanio] = numero;
// 	(*tamanio)++;

// 	*vector = bloque;
// }

int main(int argc, char *argv[])
{
	int *enteros = NULL;
	int tamanio = 0;

	agregar_numero(&enteros, &tamanio, 5);
	printf("El tamaño del vector es %i\n", tamanio);

	agregar_numero(&enteros, &tamanio, 10);
	printf("El tamaño del vector es %i\n", tamanio);
	
	agregar_numero(&enteros, &tamanio, 15);
	printf("El tamaño del vector es %i\n", tamanio);

	for(int i=0; i < tamanio; i++) {
		printf("El valor en la posicion %i es %i\n", i, enteros[i]);
	}

	free(enteros);

	return 0;
}