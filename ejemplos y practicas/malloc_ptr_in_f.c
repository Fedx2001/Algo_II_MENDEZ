#include <stdio.h>
#include <stdlib.h>

int reservar_cantidad(int **cantidad)
{
	*cantidad = malloc(sizeof(int));
	if(!*cantidad)
		return 0;
	return 1;
}
int wrapp(int *cantidad)
{
	*cantidad = malloc(sizeof(int));
	if(!*cantidad)
		return 0;
	return 1;
}

int main()
{
	int *cantidad = NULL;
	int res = reservar_cantidad(&cantidad);
	*cantidad = 1230;
	printf("%i, %i\n", *cantidad, res);
	free(cantidad);
}