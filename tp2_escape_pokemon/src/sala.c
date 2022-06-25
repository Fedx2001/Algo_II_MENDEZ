#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"
#include "lista.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LECTURA 1024
#define HASH_TAMANIO_DEFAULT 6

struct sala{
	hash_t *objetos_conocidos;
	hash_t *objetos_poseidos;
	lista_t *objetos;
	lista_t *interacciones;
	bool escape_exitoso;
};

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	if(!objetos || !interacciones) return NULL;
	
	sala_t *sala = calloc(1, sizeof(sala_t));
	if(!sala) return NULL;
	
	sala->objetos_conocidos = hash_crear(HASH_TAMANIO_DEFAULT);
	sala->objetos_poseidos = hash_crear(HASH_TAMANIO_DEFAULT);
	sala->objetos = lista_crear();
	sala->interacciones = lista_crear();
	sala->escape_exitoso = false;

	if(!sala->objetos_conocidos || !sala->objetos_poseidos || !sala->objetos || !sala->interacciones) 
		return NULL;

	char buffer[MAX_LECTURA];
	char *linea = NULL;

	FILE *f_objetos = fopen(objetos, "r");
	if(!f_objetos){
		sala_destruir(sala);
		return NULL;
	}

	linea = fgets(buffer, MAX_LECTURA, f_objetos);
	while(linea){
		struct objeto *actual = objeto_crear_desde_string(linea);
		if(!actual || !lista_insertar(sala->objetos, actual)){
			sala_destruir(sala);
			fclose(f_objetos);
			return NULL;
		}
		linea = fgets(buffer, MAX_LECTURA, f_objetos);
	}
	
	fclose(f_objetos);

	FILE *f_interacciones = fopen(interacciones, "r");
	if(!f_interacciones){
		sala_destruir(sala);
		return NULL;
	}

	linea = fgets(buffer, MAX_LECTURA, f_interacciones);
	while(linea){
		struct interaccion *actual = interaccion_crear_desde_string(linea);
		if(!actual || !lista_insertar(sala->interacciones, actual)){
			sala_destruir(sala);
			fclose(f_interacciones);
			return NULL;
		}
		linea = fgets(buffer, MAX_LECTURA, f_interacciones);
	}

	fclose(f_interacciones);

	if(lista_vacia(sala->objetos) || lista_vacia(sala->interacciones)){
		sala_destruir(sala);
		return NULL;
	}	

	if(!hash_insertar(sala->objetos_conocidos, ((struct objeto *)lista_primero(sala->objetos))->nombre,
			  lista_primero(sala->objetos), NULL)){
		sala_destruir(sala);
		return NULL;
	}

	return sala;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if(sala == NULL) {
		if(cantidad != NULL) *cantidad = -1;
		return NULL;
	}

	char **nombres_objs = malloc(lista_tamanio(sala->objetos) * sizeof(char *));
	if(nombres_objs == NULL) {
		if(cantidad != NULL) *cantidad = -1;
		return NULL;
	}

	lista_iterador_t *iterador = lista_iterador_crear(sala->objetos);

	int i = 0;
	for( ; lista_iterador_tiene_siguiente(iterador); lista_iterador_avanzar(iterador)){
		struct objeto *actual = lista_iterador_elemento_actual(iterador);
		nombres_objs[i] = actual->nombre;
		i++;
	}

	lista_iterador_destruir(iterador);

	if(cantidad != NULL) *cantidad = i;

	return nombres_objs;
}

char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
{
	if(sala == NULL) {
		if(cantidad != NULL) *cantidad = -1;
		return NULL;
	}

	char **nombres_objs = malloc(lista_tamanio(sala->objetos) * sizeof(char *));
	if(nombres_objs == NULL) {
		if(cantidad != NULL) *cantidad = -1;
		return NULL;
	}

	lista_iterador_t *iterador = lista_iterador_crear(sala->objetos);

	int i = 0;
	for( ; lista_iterador_tiene_siguiente(iterador); lista_iterador_avanzar(iterador)){
		struct objeto *actual = lista_iterador_elemento_actual(iterador);
		nombres_objs[i] = actual->nombre;
		i++;
	}

	lista_iterador_destruir(iterador);

	if(cantidad != NULL) *cantidad = i;

	return nombres_objs;
}

char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
{
	if(sala == NULL) {
		if(cantidad != NULL) *cantidad = -1;
		return NULL;
	}

	char **nombres_objs = malloc(lista_tamanio(sala->objetos) * sizeof(char *));
	if(nombres_objs == NULL) {
		if(cantidad != NULL) *cantidad = -1;
		return NULL;
	}

	lista_iterador_t *iterador = lista_iterador_crear(sala->objetos);

	int i = 0;
	for( ; lista_iterador_tiene_siguiente(iterador); lista_iterador_avanzar(iterador)){
		struct objeto *actual = lista_iterador_elemento_actual(iterador);
		nombres_objs[i] = actual->nombre;
		i++;
	}

	lista_iterador_destruir(iterador);

	if(cantidad != NULL) *cantidad = i;

	return nombres_objs;
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,
				const char *objeto2)
{
	if(sala == NULL || verbo == NULL || objeto1 == NULL) return false;

	

	return true;
}

bool sala_escape_exitoso(sala_t *sala)
{
	if(!sala) return false;

	return sala->escape_exitoso;
}

void sala_destruir(sala_t *sala)
{
	if(sala == NULL)
		return;

	lista_destruir_todo(sala->interacciones, free);
	lista_destruir_todo(sala->objetos, free);
	hash_destruir(sala->objetos_conocidos);
	hash_destruir(sala->objetos_poseidos);

	free(sala);
}
