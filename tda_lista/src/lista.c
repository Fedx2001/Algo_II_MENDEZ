#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

#define ERROR 0

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
	if(!lista)
		return NULL;

	nodo_t *nodo = malloc(sizeof(nodo_t));
	if(!nodo)
		return NULL;

	if(posicion == 0 && !lista_vacia(lista)) {
		nodo->siguiente = lista->nodo_inicio;
		nodo->elemento = elemento;

		lista->nodo_inicio = nodo;
	} else if(lista_vacia(lista) || posicion < 0 || posicion >= lista_tamanio(lista)) {
		return lista_insertar(lista, elemento);
	} else {
		nodo_t *anterior = lista->nodo_inicio;
		for(int i=1; i<posicion; i++) {
			anterior = anterior->siguiente;
		}

		nodo->siguiente = anterior->siguiente;
		anterior->siguiente = nodo;
	}

	lista->cantidad++;

	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if(!lista || lista_vacia(lista))
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
	if(!lista)
		return NULL;

	if(lista_vacia(lista))
		return NULL;

	void *elemento = NULL;

	if(posicion >= lista->cantidad || posicion < 0 || posicion == lista_tamanio(lista)-1) {
		return lista_quitar(lista);
	} else if(posicion == 0) {
		elemento = lista->nodo_inicio->elemento;
		free(lista->nodo_inicio);
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
	} else {
		nodo_t *aux = lista->nodo_inicio;
		for(int i=1; i<posicion; i++) {
			aux = aux->siguiente;
		}

		nodo_t *nodo_a_quitar = aux->siguiente; 

		elemento = nodo_a_quitar->elemento;
		aux->siguiente = nodo_a_quitar->siguiente;
		free(nodo_a_quitar);
	}

	lista->cantidad--;

	return elemento;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if(!lista)
		return NULL;
	
	if(lista_vacia(lista))
		return NULL;

	if(posicion < 0 || posicion > lista_tamanio(lista))
		return NULL;

	nodo_t *nodo = lista->nodo_inicio;
	for(int i=0; i<posicion; i++) {
		nodo = nodo->siguiente;
	}

	return nodo->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if(!lista)
		return NULL;

	if(lista_vacia(lista))
		return NULL;

	nodo_t *actual = lista->nodo_inicio;
	while(actual->siguiente) {
		if(comparador && comparador((actual->elemento), contexto))
			return actual->elemento;

		actual = actual->siguiente;
	}

	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if(!lista || lista_vacia(lista))
		return NULL;

	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if(!lista || lista_vacia(lista))
		return NULL;

	return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t *lista)
{
	if(!lista)
		return NULL;

	return lista->nodo_inicio == NULL;
}

size_t lista_tamanio(lista_t *lista)
{
	if(!lista)
		return 0;

	return lista->cantidad;
}

void lista_destruir(lista_t *lista)
{
	if(!lista)
		return;

	nodo_t *actual = lista->nodo_inicio;
	nodo_t *aux = NULL;
	if(!lista_vacia(lista)) {
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
	if(!lista)
		return;

	nodo_t *actual = lista->nodo_inicio;
	nodo_t *aux = NULL;
	if(!lista_vacia(lista)) {
		while(actual) {
			aux = actual->siguiente;
			if(funcion)
				funcion(actual->elemento);
			free(actual);
			actual = aux;
		}
	}

	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if(!lista)
		return NULL;

	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	if(!iterador)
		return NULL;

	iterador->lista = lista;
	iterador->corriente = lista->nodo_inicio;

	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if(!iterador)
		return false;

	if(iterador->corriente && iterador->corriente->siguiente)
		return true;

	return false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if(!iterador)
		return false;

	if(iterador->corriente) {
		if(iterador->corriente->siguiente) {
			iterador->corriente = iterador->corriente->siguiente;
			return true;
		} else {
			iterador->corriente = NULL;
			return true;
		}
	}

	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if(!iterador)
		return NULL;

	if(!iterador->corriente)
		return NULL;

	return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if(!lista || !funcion || !contexto)
		return ERROR;

	int cantidad_iterados = 0;

	nodo_t *actual = malloc(sizeof(nodo_t));
	if(!actual)
		return ERROR;

	while(actual) {
		if(funcion(actual->elemento, contexto) == false)
			return cantidad_iterados;
		actual = actual->siguiente;
		cantidad_iterados++;
	} 

	return cantidad_iterados;
}
