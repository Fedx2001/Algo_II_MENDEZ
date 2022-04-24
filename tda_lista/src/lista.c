#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

lista_t *lista_crear()
{
	return calloc(1, sizeof(lista_t));
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if(!lista)
		return NULL;
	
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if(!nodo)
		return NULL;

	nodo->elemento = elemento;
	nodo->siguiente = NULL;

	if(lista->nodo_inicio != NULL && lista->nodo_fin != NULL) {
		lista->nodo_fin->siguiente = nodo;
	} else if(lista->nodo_inicio == NULL) {
		lista->nodo_inicio = nodo;
	}

	lista->nodo_fin = nodo;
	lista->cantidad++;

	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	return NULL;
}

void *lista_quitar(lista_t *lista)
{
	if(!lista)
		return NULL;

	void *elemento = NULL;
	nodo_t *anterior = NULL;
	nodo_t *actual = lista->nodo_inicio;

	while(actual->siguiente) {
		anterior = actual;
		actual = actual->siguiente;
	}

	if(lista->nodo_inicio == lista->nodo_fin) {
		elemento = lista->nodo_fin->elemento;
		free(lista->nodo_fin);
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
	} else {
		elemento = actual->elemento;
		free(lista->nodo_fin);
		lista->nodo_fin = anterior;
		lista->nodo_fin->siguiente = NULL;
	}
	
	lista->cantidad--;

	return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if(!lista || !lista->nodo_inicio)
		return NULL;
	
	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if(!lista || !lista->nodo_fin)
		return NULL;
	
	return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t *lista)
{
	return lista->nodo_inicio == NULL;
}

size_t lista_tamanio(lista_t *lista)
{
	return lista->cantidad;
}

void lista_destruir(lista_t *lista)
{
	if(!lista)
		return;
	
	nodo_t *actual = lista->nodo_inicio;
	nodo_t *aux = NULL;
	if(actual) {
		while(actual) {
			aux = actual->siguiente;
			free(actual);
			actual = aux;
		}
	}

	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{

}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	return NULL;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	return false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	return NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{

}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	return 0;
}
