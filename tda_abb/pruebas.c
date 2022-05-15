#include "src/abb.h"
#include "src/lista.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

int comparar_enteros(void *a, void *b)
{
	return *(int *)a - *(int *)b;
}

void crear_un_abb_crea_un_abb_con_tamanio_0_y_raiz_nula()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	pa2m_afirmar(arbol, "Puedo crear un abb");
	pa2m_afirmar(arbol->nodo_raiz == NULL, "El arbol no tiene raiz");
	pa2m_afirmar(arbol->tamanio == 0, "El arbol tiene tamaño 0");

	abb_destruir(arbol);
}

void no_puedo_crear_un_abb_con_funcion_comparadora_nula()
{
	abb_t *arbol = abb_crear(NULL);

	pa2m_afirmar(arbol == NULL, "No puedo crear un abb con funcion comparadora nula");
}

void no_puedo_insertar_en_un_abb_null()
{
	pa2m_afirmar(abb_insertar(NULL, 0) == NULL, "No puedo insertar en un arbol NULL");
}

void puedo_insertar_un_elemento_null_en_abb()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	pa2m_afirmar(abb_insertar(arbol, NULL) == arbol, "Puedo insertar NULL en un abb (no se por qué querría hacerlo, pero puedo)");
	pa2m_afirmar(arbol->nodo_raiz->elemento == NULL, "El elemento de la raiz es NULL");
	pa2m_afirmar(arbol->tamanio, "El tamaño del arbol es 1");

	abb_destruir(arbol);
}

void insertar_en_abb_vacio_inserta_en_la_raiz()
{
	abb_t *arbol = abb_crear(comparar_enteros);
	int elemento = 10;

	abb_insertar(arbol, &elemento);

	pa2m_afirmar(arbol->nodo_raiz->elemento == &elemento, "Insertar en un abb vacio inserta en la raiz");

	abb_destruir(arbol);
}

void insertar_un_elemento_mayor_que_la_raiz_inserta_en_la_derecha_de_la_raiz()
{
	abb_t *arbol = abb_crear(comparar_enteros);
	int elementos[2] = {10, 12};

	abb_insertar(arbol, elementos+0);
	abb_insertar(arbol, elementos+1);

	pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == elementos+1, "Insertar un elemento mayor que la raiz inserta a la derecha");
	pa2m_afirmar(arbol->nodo_raiz->izquierda == NULL, "La raiz no tiene un elemento a la izquierda");

	abb_destruir(arbol);
}

void insertar_un_elemento_menor_que_la_raiz_inserta_en_la_izquierda_de_la_raiz()
{
	abb_t *arbol = abb_crear(comparar_enteros);
	int elementos[2] = {10, 7};

	abb_insertar(arbol, elementos+0);
	abb_insertar(arbol, elementos+1);

	pa2m_afirmar(arbol->nodo_raiz->izquierda->elemento == elementos+1, "Insertar un elemento menor que la raiz inserta a la izquierda");
	pa2m_afirmar(arbol->nodo_raiz->derecha == NULL, "La raiz no tiene un elemento a la derecha");

	abb_destruir(arbol);
}

void insertar_varios_elementos_inserta_en_las_posiciones_correctas()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[6] = {24,345,12,99,1,15};

	for(int i=0; i<6; i++)
		abb_insertar(arbol, elementos+i);

	bool orden_correcto = true;

	if(arbol->nodo_raiz->elemento != elementos+0)
		orden_correcto = false;
	
	if(arbol->nodo_raiz->izquierda->elemento != elementos+2)
		orden_correcto = false;
	
	if(arbol->nodo_raiz->izquierda->izquierda->elemento != elementos+4)
		orden_correcto = false;
	
	if(arbol->nodo_raiz->izquierda->derecha->elemento != elementos+5)
		orden_correcto = false;
	
	if(arbol->nodo_raiz->derecha->elemento != elementos+1)
		orden_correcto = false;
	
	if(arbol->nodo_raiz->derecha->izquierda->elemento != elementos+3)
		orden_correcto = false;

	if(arbol->nodo_raiz->derecha->derecha != NULL)
		orden_correcto = false;

	pa2m_afirmar(orden_correcto == true, "Insertar varios elementos posiciona correctamente los elementos");
	pa2m_afirmar(arbol->tamanio == 6, "El tamaño del árbol es el correcto");

	abb_destruir(arbol);
}

void no_puedo_quitar_de_un_abb_null()
{
	int elemento = 1234;
	pa2m_afirmar(abb_quitar(NULL, &elemento) == NULL, "No puedo quitar un elemento de un abb NULL");
}

bool seguir_recorriendo(void *elemento, void *aux)
{
	lista_insertar((lista_t *)aux, elemento);
	if(elemento != aux)
		return true;
	return false;
}

void iterador_interno_con_recorrido_postorden_hasta_encontrar_el_10_recorre_los_elementos_correctos()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[7] = {24,345,12,99,1,15,10};

	for(int i=0; i<7; i++)
		abb_insertar(arbol, elementos+i);

	lista_t *elementos_recorridos = lista_crear();

	abb_con_cada_elemento(arbol, POSTORDEN, seguir_recorriendo, elementos_recorridos);
	// abb_con_cada_elemento(arbol, INORDEN, seguir_recorriendo, lista_elementos);
	// abb_con_cada_elemento(arbol, PREORDEN, seguir_recorriendo, lista_elementos);

	bool condicion = elementos_recorridos->nodo_inicio->elemento == elementos+6 && elementos_recorridos->nodo_fin->siguiente == NULL;
	pa2m_afirmar(condicion == true, "Iterador interno con recorrido postorden recorre correctamente el arbol hasta encontrar el valor especificado");

	lista_destruir(elementos_recorridos);

	abb_destruir(arbol);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de ABB");
	pa2m_nuevo_grupo("Prueba de creación");
	crear_un_abb_crea_un_abb_con_tamanio_0_y_raiz_nula();
	no_puedo_crear_un_abb_con_funcion_comparadora_nula();

	pa2m_nuevo_grupo("Pruebas de Inserción");
	no_puedo_insertar_en_un_abb_null();
	puedo_insertar_un_elemento_null_en_abb();
	insertar_en_abb_vacio_inserta_en_la_raiz();
	insertar_un_elemento_mayor_que_la_raiz_inserta_en_la_derecha_de_la_raiz();
	insertar_un_elemento_menor_que_la_raiz_inserta_en_la_izquierda_de_la_raiz();
	insertar_varios_elementos_inserta_en_las_posiciones_correctas();

	pa2m_nuevo_grupo("Pruebas de Eliminación");
	no_puedo_quitar_de_un_abb_null();

	pa2m_nuevo_grupo("Pruebas de Busqueda");

	pa2m_nuevo_grupo("Inserción, borrado y búsqueda sobre el mismo árbol");

	pa2m_nuevo_grupo("Pruebas de recorridos");


	pa2m_nuevo_grupo("Pruebas de iterador interno");
	iterador_interno_con_recorrido_postorden_hasta_encontrar_el_10_recorre_los_elementos_correctos();

	pa2m_nuevo_grupo("Pruebas de");

	return pa2m_mostrar_reporte();
}
