#include "abb.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if(!comparador)
		return NULL;

	abb_t *arbol = calloc(1, sizeof(abb_t));
	if(!arbol)
		return NULL;

	arbol->comparador = comparador;

	return arbol;
}

nodo_abb_t *_abb_insertar(abb_t *arbol, nodo_abb_t *actual, void *elemento)
{
	if(!actual){
		nodo_abb_t *nodo = calloc(1, sizeof(nodo_abb_t));
		if(!nodo)
			return NULL;
		nodo->derecha = NULL;
		nodo->izquierda = NULL;
		nodo->elemento = elemento;
		return nodo;
	}

	if(arbol->comparador(actual->elemento, elemento) < 0){
		actual->derecha = _abb_insertar(arbol, actual->derecha, elemento);
	}
	else{
		actual->izquierda = _abb_insertar(arbol, actual->izquierda, elemento);
	}
	
	return actual;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if(!arbol)
		return NULL;

	arbol->nodo_raiz = _abb_insertar(arbol, arbol->nodo_raiz, elemento);
	arbol->tamanio++;

	return arbol;
}

nodo_abb_t *_buscar_predecesor_inorden(nodo_abb_t *actual, nodo_abb_t ***quitado)
{
	if(!actual->derecha){
		**quitado = actual;
		return actual->izquierda;
	}

	actual->derecha = _buscar_predecesor_inorden(actual->derecha, quitado);
	return actual;
}

nodo_abb_t *_abb_eliminar_nodo(abb_t *arbol, nodo_abb_t *actual, nodo_abb_t **quitado, void *elemento)
{
	if(!actual)
		return NULL;

	int comparacion = arbol->comparador(elemento, actual->elemento);
	if(comparacion == 0){
		if(actual->derecha && actual->izquierda){
			actual->izquierda = _buscar_predecesor_inorden(actual->izquierda, &quitado);
			
			void *aux = actual->elemento;
			
			actual->elemento = (*quitado)->elemento;
			
			(*quitado)->elemento = aux;

			return actual;
		}

		*quitado = actual;
	
		if(actual->derecha)
			return actual->derecha;
		return actual->izquierda;
	} 
	
	if(comparacion < 0)
		actual->izquierda = _abb_eliminar_nodo(arbol, actual->izquierda, quitado, elemento);
	else
		actual->derecha = _abb_eliminar_nodo(arbol, actual->derecha, quitado, elemento);

	return actual;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if(!arbol || !arbol->nodo_raiz)
		return NULL;

	nodo_abb_t *quitado = NULL;
	
	arbol->nodo_raiz = _abb_eliminar_nodo(arbol, arbol->nodo_raiz, &quitado, elemento);

	if(!quitado)
		return NULL;

	void *elemento_extraido = quitado->elemento;
	free(quitado);

	arbol->tamanio--;

	return elemento_extraido;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	return NULL;
}

bool abb_vacio(abb_t *arbol)
{
	if(arbol && arbol->nodo_raiz)
		return true;

	return false;
}

size_t abb_tamanio(abb_t *arbol)
{
	if(!arbol)
		return 0;

	return arbol->tamanio;
}

void _abb_destruir(nodo_abb_t *actual, void (*destructor)(void *))
{
	if(!actual)
		return;

	_abb_destruir(actual->izquierda, destructor);
	_abb_destruir(actual->derecha, destructor);
	if(destructor)
		destructor(actual->elemento);
	free(actual);
}

void abb_destruir(abb_t *arbol)
{
	_abb_destruir(arbol->nodo_raiz, NULL);
	free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	_abb_destruir(arbol->nodo_raiz, destructor);
	free(arbol);
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	return 0;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	return 0;
}
