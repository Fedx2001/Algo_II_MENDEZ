#include <stdio.h>

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
 * 
 */
int main(int argc, char *argv[])
{
	char numeros[3];
	numeros[0] = 10;
	numeros[1] = 99;
	numeros[2] = 42;

	char *puntero_numeros = numeros;

	printf("El segundo numero es: %i\n", numero[1]);
	printf("El segundo numero tambien es: %i\n", puntero_numeros[1]);
	printf("El segundo numero tambien es: %i\n", *(puntero_numeros+1));

	return 0;
}