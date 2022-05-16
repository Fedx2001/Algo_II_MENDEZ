#include "abb.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define COMPARACION_EXITOSA 0
#define TAMANIO_ARBOL_NULL 0
#define PARAR_RECORRIDO false

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

	if(arbol->comparador(actual->elemento, elemento) < COMPARACION_EXITOSA)
		actual->derecha = _abb_insertar(arbol, actual->derecha, elemento);
	else
		actual->izquierda = _abb_insertar(arbol, actual->izquierda, elemento);

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

nodo_abb_t *_abb_eliminar_nodo(abb_comparador comparador, nodo_abb_t *actual, nodo_abb_t **quitado, void *elemento)
{
	if(!actual)
		return NULL;

	int comparacion = comparador(elemento, actual->elemento);
	if(comparacion == COMPARACION_EXITOSA){
		*quitado = actual;

		if(actual->derecha && actual->izquierda){
			actual->izquierda = _buscar_predecesor_inorden(actual->izquierda, &quitado);

			void *aux = actual->elemento;

			actual->elemento = (*quitado)->elemento;

			(*quitado)->elemento = aux;

			return actual;
		}

		if(actual->derecha)
			return actual->derecha;
		return actual->izquierda;
	}

	if(comparacion < COMPARACION_EXITOSA)
		actual->izquierda = _abb_eliminar_nodo(comparador, actual->izquierda, quitado, elemento);
	else
		actual->derecha = _abb_eliminar_nodo(comparador, actual->derecha, quitado, elemento);

	return actual;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if(!arbol)
		return NULL;

	nodo_abb_t *quitado = NULL;
	void *elemento_extraido = NULL;

	arbol->nodo_raiz = _abb_eliminar_nodo(arbol->comparador, arbol->nodo_raiz, &quitado, elemento);

	if(quitado){
		elemento_extraido = quitado->elemento;
		free(quitado);
		arbol->tamanio--;
	}

	return elemento_extraido;
}

void *_buscar_elemento_en_nodo(nodo_abb_t *actual, void *elemento, abb_comparador comparador)
{
	if(!actual)
		return NULL;

	int comparacion = comparador(elemento, actual->elemento);

	if(comparacion == COMPARACION_EXITOSA)
		return actual->elemento;

	if(comparacion < COMPARACION_EXITOSA)
		return _buscar_elemento_en_nodo(actual->izquierda, elemento, comparador);
	else
		return _buscar_elemento_en_nodo(actual->derecha, elemento, comparador);
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if(!arbol)
		return NULL;

	return _buscar_elemento_en_nodo(arbol->nodo_raiz, elemento, arbol->comparador);
}

bool abb_vacio(abb_t *arbol)
{
	if(arbol && !arbol->nodo_raiz)
		return true;

	return false;
}

size_t abb_tamanio(abb_t *arbol)
{
	if(!arbol)
		return TAMANIO_ARBOL_NULL;

	return arbol->tamanio;
}

void _abb_destruir_nodos(nodo_abb_t *actual, void (*destructor)(void *))
{
	if(!actual)
		return;

	_abb_destruir_nodos(actual->izquierda, destructor);
	_abb_destruir_nodos(actual->derecha, destructor);
	if(destructor)
		destructor(actual->elemento);
	free(actual);
}

void abb_destruir(abb_t *arbol)
{
	_abb_destruir_nodos(arbol->nodo_raiz, NULL);
	free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	_abb_destruir_nodos(arbol->nodo_raiz, destructor);
	free(arbol);
}

void _con_cada_elemento_inorden(nodo_abb_t *actual, bool (*funcion)(void *, void *), void *aux, size_t *veces_invocada, bool *cortar_ejecucion)
{
	if(!actual)
		return;

	_con_cada_elemento_inorden(actual->izquierda, funcion, aux, veces_invocada, cortar_ejecucion);

	if(*cortar_ejecucion == PARAR_RECORRIDO)
		return;
	*cortar_ejecucion = funcion(actual->elemento, aux);
	*veces_invocada = *veces_invocada + 1;
	
	_con_cada_elemento_inorden(actual->derecha, funcion, aux, veces_invocada, cortar_ejecucion);
}

void _con_cada_elemento_preorden(nodo_abb_t *actual, bool (*funcion)(void *, void *), void *aux, size_t *veces_invocada, bool *cortar_ejecucion)
{
	if(!actual)
		return;

	if(*cortar_ejecucion == PARAR_RECORRIDO)
		return;
	*cortar_ejecucion = funcion(actual->elemento, aux);
	*veces_invocada = *veces_invocada + 1;

	_con_cada_elemento_preorden(actual->izquierda, funcion, aux, veces_invocada, cortar_ejecucion);
	_con_cada_elemento_preorden(actual->derecha, funcion, aux, veces_invocada, cortar_ejecucion);
}

void _con_cada_elemento_postorden(nodo_abb_t *actual, bool (*funcion)(void *, void *), void *aux, size_t *veces_invocada, bool *cortar_ejecucion)
{
	if(!actual)
		return;

	_con_cada_elemento_postorden(actual->izquierda, funcion, aux, veces_invocada, cortar_ejecucion);
	_con_cada_elemento_postorden(actual->derecha, funcion, aux, veces_invocada, cortar_ejecucion);

	if(*cortar_ejecucion == PARAR_RECORRIDO)
		return;
	*cortar_ejecucion = funcion(actual->elemento, aux);
	*veces_invocada = *veces_invocada + 1;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	size_t veces_invocada = 0;
	if(!arbol || !funcion)
		return veces_invocada;

	bool cortar_ejecucion = true;

	switch(recorrido)
	{
	case INORDEN:
		_con_cada_elemento_inorden(arbol->nodo_raiz, funcion, aux, &veces_invocada, &cortar_ejecucion);
		break;
	case POSTORDEN:
		_con_cada_elemento_postorden(arbol->nodo_raiz, funcion, aux, &veces_invocada, &cortar_ejecucion);
		break;
	case PREORDEN:
		_con_cada_elemento_preorden(arbol->nodo_raiz, funcion, aux, &veces_invocada, &cortar_ejecucion);
		break;
	}

	return veces_invocada;
}

void _recorrido_inorden(nodo_abb_t *actual, void **array, size_t tamanio_array, size_t *elementos_guardados)
{
	if(!actual || *elementos_guardados >= tamanio_array)
		return;

	_recorrido_inorden(actual->izquierda, array, tamanio_array, elementos_guardados);
	
	void *elemento = actual->elemento;
	array[*elementos_guardados] = elemento;
	*elementos_guardados = *elementos_guardados + 1;

	_recorrido_inorden(actual->derecha, array, tamanio_array, elementos_guardados);
}

void _recorrido_postorden(nodo_abb_t *actual, void **array, size_t tamanio_array, size_t *elementos_guardados)
{
	if(!actual)
		return;

	_recorrido_inorden(actual->izquierda, array, tamanio_array, elementos_guardados);
	_recorrido_inorden(actual->derecha, array, tamanio_array, elementos_guardados);
	
	if(*elementos_guardados >= tamanio_array)
		return;
	void *elemento = actual->elemento;
	array[*elementos_guardados] = elemento;
	*elementos_guardados = *elementos_guardados + 1;
}

void _recorrido_preorden(nodo_abb_t *actual, void **array, size_t tamanio_array, size_t *elementos_guardados)
{
	if(!actual || *elementos_guardados >= tamanio_array)
		return;

	void *elemento = actual->elemento;
	array[*elementos_guardados] = elemento;
	*elementos_guardados = *elementos_guardados + 1;
	
	_recorrido_inorden(actual->izquierda, array, tamanio_array, elementos_guardados);
	_recorrido_inorden(actual->derecha, array, tamanio_array, elementos_guardados);
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	size_t elementos_guardados = 0;
	if(!arbol || !array || tamanio_array == 0)
		return elementos_guardados;

	switch(recorrido)
	{
	case INORDEN:
		_recorrido_inorden(arbol->nodo_raiz, array, tamanio_array, &elementos_guardados);
		break;
	case POSTORDEN:
		_recorrido_postorden(arbol->nodo_raiz, array, tamanio_array, &elementos_guardados);
		break;
	case PREORDEN:
		_recorrido_preorden(arbol->nodo_raiz, array, tamanio_array, &elementos_guardados);
		break;
	}

	return elementos_guardados;
}
