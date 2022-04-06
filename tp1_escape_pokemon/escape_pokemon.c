#include "src/sala.h"
#include "src/liberar_nombres.h"
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
	if(nombres == NULL || cantidad == NULL)
		return;

	for(int i = 0; i < *cantidad; i++) {
		printf("%i: %s\n", i, nombres[i]);
	}
}

/*
 * Recibe un flag booleano y devuelve un texto indicando si es válido o no.
 *
 * Resulta valido si el flag es true, e invalido si el flag es false.
 */
char *pasear_bool_a_texto(bool flag)
{
	return (flag ? "Válido" : "Inválido");
}

int main(int argc, char *argv[])
{
	if(argc != 3)
		return -1;

	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);

	if(sala != NULL) {
		printf("Objetos...\n");
		int *cant_og = NULL;
		printf("Cantidad esta en %p\n", &cant_og);
		printf("Cantidad apunta a %p\n", cant_og);
		char **nombres_objetos = sala_obtener_nombre_objetos(sala, cant_og);
		printf("Cantidad apunta a %p\n", cant_og);
		mostrar_nombres_objetos(nombres_objetos, cant_og);
		printf("%i\n", *cant_og);

		printf("Interacciones...\n");
		bool interacc_es_valida;

		interacc_es_valida = sala_es_interaccion_valida(sala, "examinar", "habitacion", "");
		printf("Examinar la habitacion: %s\n", pasear_bool_a_texto(interacc_es_valida));
		interacc_es_valida = sala_es_interaccion_valida(sala, "abrir", "pokebola", "_");
		printf("Abrir pokebola: %s\n", pasear_bool_a_texto(interacc_es_valida));
		interacc_es_valida = sala_es_interaccion_valida(sala, "usar", "llave", "cajon");
		printf("Usar llave en el cajon: %s\n", pasear_bool_a_texto(interacc_es_valida));
		interacc_es_valida = sala_es_interaccion_valida(sala, "quemar", "mesa", "");
		printf("Quemar la mesa: %s\n", pasear_bool_a_texto(interacc_es_valida));

		liberar_nombres(nombres_objetos, cant_og);
		sala_destruir(sala);
	}
	return 0;
}