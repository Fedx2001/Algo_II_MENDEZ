#include "abb.h"
#include <stddef.h>
#include <stdlib.h>

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
		nodo->elemento = elemento;
		return nodo;
	}

	if(arbol->comparador(actual->elemento, elemento) < 0){
		actual->izquierda = _abb_insertar(arbol, actual->izquierda, elemento);
	}
	else{
		actual->derecha = _abb_insertar(arbol, actual->derecha, elemento);
	}
	
	return actual;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if(!arbol)
		return NULL;

	arbol->nodo_raiz = _abb_insertar(arbol, arbol->nodo_raiz, elemento);

	return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	return NULL;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	return NULL;
}

bool abb_vacio(abb_t *arbol)
{
	return true;
}

size_t abb_tamanio(abb_t *arbol)
{
	return 0;
}

void abb_destruir(abb_t *arbol)
{
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
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
