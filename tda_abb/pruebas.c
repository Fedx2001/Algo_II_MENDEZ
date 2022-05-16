#include "src/abb.h"
#include "src/cola.h"
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

void no_puedo_quitar_de_un_abb_vacio()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[6] = {24,345,12,99,1,15};

	for(int i=0; i<6; i++)
		abb_insertar(arbol, elementos+i);

	int a_borrar = 25;

	pa2m_afirmar(abb_quitar(arbol, &a_borrar) == NULL, "No puedo quitar un elemento de un abb vacio");

	abb_destruir(arbol);
}

void no_puedo_quitar_un_elemento_que_no_existe_en_un_abb()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	char elemento = 123;

	pa2m_afirmar(abb_quitar(arbol, &elemento) == NULL, "No puedo quitar un elemento que no existe del abb");

	abb_destruir(arbol);
}

void quitar_la_raiz_en_un_abb_con_un_solo_elemento_deja_al_abb_vacio_y_con_tamanio_0()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elemento = 100;
	arbol = abb_insertar(arbol, &elemento);

	pa2m_afirmar(abb_quitar(arbol, &elemento) == &elemento, "Puedo quitar la raiz de un abb con un elemento");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "El tamanio del abb luego de quitar es 0");
	pa2m_afirmar(abb_vacio(arbol) == true, "El arbol esta vacio luego de quitar");

	abb_destruir(arbol);
}

void quitar_un_nodo_hoja_actualiza_correctamente_el_arbol()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[4] = {24,326,10,9};
	for(int i=0; i<4; i++)
		abb_insertar(arbol, elementos+i);

	int *quitado = abb_quitar(arbol, elementos+3);

	bool orden_correcto = true;
	if(arbol->nodo_raiz->elemento != elementos+0)
		orden_correcto = false;

	if(arbol->nodo_raiz->derecha->elemento != elementos+1)
		orden_correcto = false;

	if(arbol->nodo_raiz->izquierda->elemento != elementos+2)
		orden_correcto = false;

	if(arbol->nodo_raiz->izquierda->izquierda != NULL)
		orden_correcto = false;

	pa2m_afirmar(quitado == elementos+1, "Se quitó un elemento sin hijos");
	pa2m_afirmar(orden_correcto == true, "El arbol esta correctamente formado");
	pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == elementos+3, "Luego de quitar el hijo queda en lugar del elemento quitado");

	abb_destruir(arbol);
}

void quitar_un_nodo_con_hijo_derecho_actualiza_correctamente_los_nodos_y_el_tamanio()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[6] = {24,99,12,100,1,15};
	for(int i=0; i<6; i++)
		abb_insertar(arbol, elementos+i);

	int *quitado = abb_quitar(arbol, elementos+1);

	bool orden_correcto = true;
	if(arbol->nodo_raiz->elemento != elementos+0)
		orden_correcto = false;

	if(arbol->nodo_raiz->derecha->elemento != elementos+3)
		orden_correcto = false;

	if(arbol->nodo_raiz->izquierda->elemento != elementos+2)
		orden_correcto = false;
	
	if(arbol->nodo_raiz->derecha->derecha != NULL)
		orden_correcto = false;

	if(arbol->nodo_raiz->izquierda->izquierda->elemento != elementos+4)
		orden_correcto = false;

	if(arbol->nodo_raiz->izquierda->derecha->elemento != elementos+5)
		orden_correcto = false;

	pa2m_afirmar(quitado == elementos+1, "Se quitó un elemento con hijo derecho");
	pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == elementos+3, "Luego de quitar el hijo queda en lugar del elemento quitado");
	pa2m_afirmar(abb_tamanio(arbol) == 5, "El tamaño se actualiza correctamente");
	pa2m_afirmar(orden_correcto == true, "El arbol esta correctamente formado");

	abb_destruir(arbol);
}

void quitar_un_nodo_con_hijo_izquierdo_actualiza_correctamente_los_nodos_y_el_tamanio()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[6] = {24,99,12,98,1,15};
	for(int i=0; i<6; i++)
		abb_insertar(arbol, elementos+i);

	int *quitado = abb_quitar(arbol, elementos+1);

	bool orden_correcto = true;
	if(arbol->nodo_raiz->elemento != elementos+0)
		orden_correcto = false;

	if(arbol->nodo_raiz->derecha->elemento != elementos+3)
		orden_correcto = false;

	if(arbol->nodo_raiz->izquierda->elemento != elementos+2)
		orden_correcto = false;
	
	if(arbol->nodo_raiz->derecha->izquierda != NULL)
		orden_correcto = false;

	if(arbol->nodo_raiz->izquierda->izquierda->elemento != elementos+4)
		orden_correcto = false;

	if(arbol->nodo_raiz->izquierda->derecha->elemento != elementos+5)
		orden_correcto = false;

	pa2m_afirmar(quitado == elementos+1, "Se quitó un elemento con hijo izquierdo");
	pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == elementos+3, "Luego de quitar el hijo queda en lugar del elemento quitado");
	pa2m_afirmar(abb_tamanio(arbol) == 5, "El tamaño se actualiza correctamente");
	pa2m_afirmar(orden_correcto == true, "El arbol esta correctamente formado");

	abb_destruir(arbol);
}

void quitar_un_nodo_con_hijos_a_ambos_lados_actualiza_correctamente_los_nodos_y_el_tamanio()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[6] = {24,99,12,100,1,15};
	for(int i=0; i<6; i++)
		abb_insertar(arbol, elementos+i);

	int *quitado = abb_quitar(arbol, elementos+2);

	bool orden_correcto = true;
	if(arbol->nodo_raiz->elemento != elementos+0)
		orden_correcto = false;

	if(arbol->nodo_raiz->derecha->elemento != elementos+1)
		orden_correcto = false;

	if(arbol->nodo_raiz->izquierda->elemento != elementos+4)
		orden_correcto = false;
	
	if(arbol->nodo_raiz->derecha->derecha->elemento != elementos+3)
		orden_correcto = false;

	if(arbol->nodo_raiz->izquierda->izquierda != NULL)
		orden_correcto = false;

	if(arbol->nodo_raiz->izquierda->derecha->elemento != elementos+5)
		orden_correcto = false;

	pa2m_afirmar(quitado == elementos+2, "Se quitó un elemento con hijos a ambos lados");
	pa2m_afirmar(arbol->nodo_raiz->izquierda->elemento == elementos+4, "Luego de quitar, el predecesor inorden queda en lugar del elemento quitado");
	pa2m_afirmar(abb_tamanio(arbol) == 5, "El tamaño se actualiza correctamente");
	pa2m_afirmar(orden_correcto == true, "El arbol esta correctamente formado");

	abb_destruir(arbol);
}

void quitar_la_raiz_actualiza_correctamente_el_nodo_raiz()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[6] = {24,99,12,100,1,15};
	for(int i=0; i<6; i++)
		abb_insertar(arbol, elementos+i);

	int *quitado = abb_quitar(arbol, elementos);

	bool orden_correcto = true;
	if(arbol->nodo_raiz->elemento != elementos+5)
		orden_correcto = false;

	if(arbol->nodo_raiz->derecha->elemento != elementos+1)
		orden_correcto = false;

	if(arbol->nodo_raiz->izquierda->elemento != elementos+2)
		orden_correcto = false;
	
	if(arbol->nodo_raiz->derecha->derecha->elemento != elementos+3)
		orden_correcto = false;

	if(arbol->nodo_raiz->izquierda->izquierda->elemento != elementos+4)
		orden_correcto = false;

	if(arbol->nodo_raiz->izquierda->derecha != NULL)
		orden_correcto = false;

	pa2m_afirmar(quitado == elementos, "Se quitó el elemento de la raiz");
	pa2m_afirmar(arbol->nodo_raiz->elemento == elementos+5, "Luego de quitar la raiz, el predecesor inorden toma su lugar");
	pa2m_afirmar(abb_tamanio(arbol) == 5, "El tamaño se actualiza correctamente");
	pa2m_afirmar(orden_correcto == true, "El arbol esta correctamente formado");

	abb_destruir(arbol);
}

void no_puedo_buscar_en_abb_nulo()
{
	char elemento = 56;
	pa2m_afirmar(abb_buscar(NULL, &elemento) == NULL, "No puedo buscar en un abb NULL");
}

void buscar_un_elemento_que_no_existe_en_el_abb_devuelve_null()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	char elementos[5] = {12,43,5,10,49};
	for(int i=0; i<5; i++)
		abb_insertar(arbol, elementos+i);

	char buscado = 56;

	pa2m_afirmar(abb_buscar(arbol, &buscado) == NULL, "Buscar un elemento que no existe devuelve NULL");

	abb_destruir(arbol);
}

void buscar_un_elemento_existente_en_el_arbol_devuelve_el_elemento()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[5] = {22,44,15,19,49};
	for(int i=0; i<5; i++)
		abb_insertar(arbol, elementos+i);

	int buscado = 19;

	pa2m_afirmar(abb_buscar(arbol, &buscado) == elementos+3, "Buscar un elemento existente devuelve el elemento");

	abb_destruir(arbol);
}

void buscar_raiz_de_un_arbol_con_un_elemento_devuelve_el_elemento_de_la_raiz()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elemento = 23;
	abb_insertar(arbol, &elemento);

	int buscado = 23;

	pa2m_afirmar(abb_buscar(arbol, &buscado) == &elemento, "Buscar la raiz en un arbol con un elemento devuelve la raiz");

	abb_destruir(arbol);
}

void buscar_un_elemento_luego_de_borrar_otro_encuentra_el_elemento()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[5] = {22,44,15,19,49};
	for(int i=0; i<5; i++)
		abb_insertar(arbol, elementos+i);

	abb_quitar(arbol, elementos+2);

	int buscado = 19;

	pa2m_afirmar(abb_buscar(arbol, &buscado) == elementos+3, "Buscar un elemento luego de borrar otro devuelve el elemento");

	abb_destruir(arbol);
}

void buscar_un_elemento_recien_insertado_encuentra_el_elemento()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[5] = {22,44,15,19,49};
	for(int i=0; i<5; i++)
		abb_insertar(arbol, elementos+i);

	int nuevo_elemento = 45;
	abb_insertar(arbol, &nuevo_elemento);

	int buscado = 45;

	pa2m_afirmar(abb_buscar(arbol, &buscado) == &nuevo_elemento, "Buscar un elemento recien insertado devuelve el elemento");

	abb_destruir(arbol);
}

void insertar_luego_de_borrar_varios_elementos_actualiza_correctamente_el_arbol()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[5] = {22,44,15,19,49};
	for(int i=0; i<5; i++)
		abb_insertar(arbol, elementos+i);

	abb_quitar(arbol, elementos+1);
	abb_quitar(arbol, elementos+4);

	int buscado = 15;

	pa2m_afirmar(abb_buscar(arbol, &buscado) == elementos+2, "Buscar un elemento luego de borrar varios elementos devuelve el elemento");

	abb_destruir(arbol);
}

void buscar_luego_borrar_e_insertar_varios_elementos_encuentra_el_elemento()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[10] = {22,44,15,19,49,23,56,9,4,1};
	for(int i=0; i<5; i++)
		abb_insertar(arbol, elementos+i);

	abb_quitar(arbol, elementos+1);
	abb_quitar(arbol, elementos+2);
	abb_quitar(arbol, elementos+4);

	for(int i=5; i<10; i++)
		abb_insertar(arbol, elementos+i);

	int buscado1 = 19;
	int buscado2 = 9;
	int buscado3 = 44;

	pa2m_afirmar(abb_buscar(arbol, &buscado1) == elementos+3, "Buscar un elemento luego de insertar y borrar varios elementos encuentra el elemento");
	pa2m_afirmar(abb_buscar(arbol, &buscado2) == elementos+7, "Buscar un elemento insertado luego de borrar devuelve el elemento");
	pa2m_afirmar(abb_buscar(arbol, &buscado3) == NULL, "Buscar un elemento que fue recientemente borrado no encuentra el elemento");

	abb_destruir(arbol);
}

bool seguir_recorriendo(void *elemento, void *aux)
{
	if(elemento != aux)
		return true;
	return false;
}

void no_puedo_usar_el_iterador_interno_con_arbol_null()
{
	pa2m_afirmar(abb_con_cada_elemento(NULL, POSTORDEN, seguir_recorriendo, NULL) == 0, "No puedo usar el iterador interno con arbol NULL");
}

void no_puedo_usar_el_iterador_interno_con_funcion_null()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[10] = {22,44,15,19,49,23,56,9,4,1};
	for(int i=0; i<10; i++)
		abb_insertar(arbol, elementos+i);

	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, NULL, NULL) == 0, "No puedo usar el iterador interno con funcion NULL");

	abb_destruir(arbol);
}

void iterador_interno_de_un_arbol_vacio_invoca_a_la_funcion_0_veces()
{
	abb_t *arbol = abb_crear(comparar_enteros);
	int elemento = 100;

	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, seguir_recorriendo, &elemento) == 0, "It. interno con arbol vacio no invoca a la funcion");

	abb_destruir(arbol);
}

void con_cada_elemento_con_recorrido_postorden_hasta_encontrar_el_10_invoca_a_la_funcion_una_sola_vez()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[7] = {24,345,12,99,1,15,10};

	for(int i=0; i<7; i++)
		abb_insertar(arbol, elementos+i);

	size_t veces_invocada = abb_con_cada_elemento(arbol, POSTORDEN, seguir_recorriendo, elementos+6);

	pa2m_afirmar(veces_invocada == 1, "It. interno con recorrido postorden hasta el 10 invoca a la funcion una vez");

	abb_destruir(arbol);
}

void con_cada_elemento_con_recorrido_preorden_hasta_encontrar_el_10_invoca_a_la_funcion_cuatro_veces()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[7] = {24,345,12,99,1,15,10};

	for(int i=0; i<7; i++)
		abb_insertar(arbol, elementos+i);

	size_t veces_invocada = abb_con_cada_elemento(arbol, PREORDEN, seguir_recorriendo, elementos+6);

	pa2m_afirmar(veces_invocada == 4, "It. interno con recorrido preorden hasta el 10 invoca a la funcion cuatro veces");

	abb_destruir(arbol);
}

void con_cada_elemento_con_recorrido_inorden_hasta_encontrar_el_10_invoca_a_la_funcion_dos_veces()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[7] = {24,345,12,99,1,15,10};

	for(int i=0; i<7; i++)
		abb_insertar(arbol, elementos+i);

	size_t veces_invocada = abb_con_cada_elemento(arbol, INORDEN, seguir_recorriendo, elementos+6);

	pa2m_afirmar(veces_invocada == 2, "It. interno con recorrido inorden hasta el 10 invoca a la funcion dos veces");

	abb_destruir(arbol);
}

bool seguir_recorriendo_con_cola(void *elemento, void *aux)
{
	cola_t *cola = aux;
	cola_encolar(cola, elemento);
	if(elemento != cola_frente(cola))
		return true;
	return false;
}

void con_cada_elemento_con_recorrido_postorden_recorre_los_elementos_correctos_hasta_encontrar_el_10()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[7] = {24,345,12,99,1,15,10};

	for(int i=0; i<7; i++)
		abb_insertar(arbol, elementos+i);

	cola_t *elementos_recorridos = cola_crear();
	cola_encolar(elementos_recorridos, elementos+6);

	abb_con_cada_elemento(arbol, POSTORDEN, seguir_recorriendo_con_cola, elementos_recorridos);

	cola_desencolar(elementos_recorridos);

	bool recorrido_correcto = true;
	if(cola_frente(elementos_recorridos) != elementos+6)
		recorrido_correcto = false;
	
	cola_desencolar(elementos_recorridos);

	if(cola_vacia(elementos_recorridos) != true)
		recorrido_correcto = false;

	pa2m_afirmar(recorrido_correcto == true, "El elemento recorrido en POSTORDEN fue el correcto");

	cola_destruir(elementos_recorridos);

	abb_destruir(arbol);
}

void con_cada_elemento_con_recorrido_preorden_recorre_los_elementos_correctos_hasta_encontrar_el_10()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[7] = {24,345,12,99,1,15,10};

	for(int i=0; i<7; i++)
		abb_insertar(arbol, elementos+i);

	cola_t *elementos_recorridos = cola_crear();
	cola_encolar(elementos_recorridos, elementos+6);

	abb_con_cada_elemento(arbol, PREORDEN, seguir_recorriendo_con_cola, elementos_recorridos);

	cola_desencolar(elementos_recorridos);

	bool recorrido_correcto = true;
	if(cola_frente(elementos_recorridos) != elementos)
		recorrido_correcto = false;

	cola_desencolar(elementos_recorridos);
	if(cola_frente(elementos_recorridos) != elementos+2)
		recorrido_correcto = false;

	cola_desencolar(elementos_recorridos);
	if(cola_frente(elementos_recorridos) != elementos+4)
		recorrido_correcto = false;

	cola_desencolar(elementos_recorridos);
	if(cola_frente(elementos_recorridos) != elementos+6)
		recorrido_correcto = false;

	cola_desencolar(elementos_recorridos);
	if(cola_vacia(elementos_recorridos) != true)
		recorrido_correcto = false;

	pa2m_afirmar(recorrido_correcto == true, "Los elementos recorridos en PREORDEN fueron los correctos");

	cola_destruir(elementos_recorridos);

	abb_destruir(arbol);
}

void con_cada_elemento_con_recorrido_inorden_recorre_los_elementos_correctos_hasta_encontrar_el_10()
{
	abb_t *arbol = abb_crear(comparar_enteros);

	int elementos[7] = {24,345,12,99,1,15,10};

	for(int i=0; i<7; i++)
		abb_insertar(arbol, elementos+i);

	cola_t *elementos_recorridos = cola_crear();
	cola_encolar(elementos_recorridos, elementos+6);

	abb_con_cada_elemento(arbol, INORDEN, seguir_recorriendo_con_cola, elementos_recorridos);

	cola_desencolar(elementos_recorridos);

	bool recorrido_correcto = true;
	if(cola_frente(elementos_recorridos) != elementos+4)
		recorrido_correcto = false;

	cola_desencolar(elementos_recorridos);
	if(cola_frente(elementos_recorridos) != elementos+6)
		recorrido_correcto = false;

	cola_desencolar(elementos_recorridos);
	if(cola_vacia(elementos_recorridos) != true)
		recorrido_correcto = false;

	pa2m_afirmar(recorrido_correcto == true, "Los elementos recorridos en INORDEN fueron los correctos");

	cola_destruir(elementos_recorridos);

	abb_destruir(arbol);
}

void recorrer_con_abb_nulo_no_hace_nada()
{
	void *array[3] = {NULL, NULL, NULL};
	pa2m_afirmar(abb_recorrer(NULL, INORDEN, array, 3) == 0, "Recorrer un abb NULL no hace nada");
}

void recorrer_con_array_nulo_no_hace_nada()
{
	abb_t *abb = abb_crear(comparar_enteros);
	int elementos[7] = {24,345,12,99,1,15,10};

	for(int i=0; i<7; i++)
		abb_insertar(abb, elementos+i);

	pa2m_afirmar(abb_recorrer(abb, INORDEN, NULL, 8) == 0, "Recorrer un abb con array NULL no hace nada");

	abb_destruir(abb);
}

void recorrer_con_tamanio_array_0_no_hace_nada()
{
	abb_t *abb = abb_crear(comparar_enteros);
	int elementos[7] = {24,345,12,99,1,15,10};

	for(int i=0; i<7; i++)
		abb_insertar(abb, elementos+i);

	void *array[5];

	pa2m_afirmar(abb_recorrer(abb, INORDEN, array, 0) == 0, "Recorrer un abb con un array de tamaño 0 no hace nada");

	abb_destruir(abb);
}

void recorrer_un_abb_con_postorden_guarda_la_cantidad_de_elementos_indicada_en_el_orden_correcto()
{
	abb_t *abb = abb_crear(comparar_enteros);
	int elementos[7] = {24,345,12,99,1,15,10};

	for(int i=0; i<7; i++)
		abb_insertar(abb, elementos+i);

	void *array[5] = {NULL, NULL, NULL, NULL, NULL};

	pa2m_afirmar(abb_recorrer(abb, POSTORDEN, array, 5) == 5, "Recorrer un abb POSTORDEN con un array de tamaño 5 guarda 5 elementos");

	bool recorrido_correcto = true;
	if(array[0] != elementos+6)
		recorrido_correcto = false;

	if(array[1] != elementos+4)
		recorrido_correcto = false;

	if(array[2] != elementos+5)
		recorrido_correcto = false;

	if(array[3] != elementos+2)
		recorrido_correcto = false;

	if(array[4] != elementos+3)
		recorrido_correcto = false;

	pa2m_afirmar(recorrido_correcto == true, "Los elementos guardados estan en POSTORDEN");

	abb_destruir(abb);
}

void recorrer_un_abb_con_preorden_guarda_la_cantidad_de_elementos_indicada_en_el_orden_correcto()
{
	abb_t *abb = abb_crear(comparar_enteros);
	int elementos[7] = {24,345,12,99,1,15,10};

	for(int i=0; i<7; i++)
		abb_insertar(abb, elementos+i);

	void *array[5] = {NULL, NULL, NULL, NULL, NULL};

	pa2m_afirmar(abb_recorrer(abb, PREORDEN, array, 5) == 5, "Recorrer un abb PREORDEN con un array de tamaño 5 guarda 5 elementos");

	bool recorrido_correcto = true;
	if(array[0] != elementos)
		recorrido_correcto = false;

	if(array[1] != elementos+2)
		recorrido_correcto = false;

	if(array[2] != elementos+4)
		recorrido_correcto = false;

	if(array[3] != elementos+6)
		recorrido_correcto = false;

	if(array[4] != elementos+5)
		recorrido_correcto = false;

	pa2m_afirmar(recorrido_correcto == true, "Los elementos guardados estan en PREORDEN");

	abb_destruir(abb);
}

void recorrer_un_abb_con_inorden_guarda_la_cantidad_de_elementos_indicada_en_el_orden_correcto()
{
	abb_t *abb = abb_crear(comparar_enteros);
	int elementos[7] = {24,345,12,99,1,15,10};

	for(int i=0; i<7; i++)
		abb_insertar(abb, elementos+i);

	void *array[5] = {NULL, NULL, NULL, NULL, NULL};

	pa2m_afirmar(abb_recorrer(abb, INORDEN, array, 5) == 5, "Recorrer un abb INORDEN con un array de tamaño 5 guarda 5 elementos");

	bool recorrido_correcto = true;
	if(array[0] != elementos+4)
		recorrido_correcto = false;

	if(array[1] != elementos+6)
		recorrido_correcto = false;

	if(array[2] != elementos+2)
		recorrido_correcto = false;

	if(array[3] != elementos+5)
		recorrido_correcto = false;

	if(array[4] != elementos)
		recorrido_correcto = false;

	pa2m_afirmar(recorrido_correcto == true, "Los elementos guardados estan INORDEN");

	abb_destruir(abb);
}

void los_recorridos_de_un_abb_con_un_array_de_mayor_tamanio_que_el_abb_solo_guardan_los_elementos_del_abb()
{
	abb_t *abb = abb_crear(comparar_enteros);
	int elementos[7] = {24,345,12,99,1,15,10};

	for(int i=0; i<7; i++)
		abb_insertar(abb, elementos+i);

	void *array[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

	pa2m_afirmar(abb_recorrer(abb, POSTORDEN, array, 10) == 7, "Recorrer en POSTORDEN con un array de mayor tamaño que el abb guarda solo los elementos del arbol");
	pa2m_afirmar(array[7] == NULL && array[8] == NULL && array[9] == NULL, "No se guardan elementos extra");
	
	pa2m_afirmar(abb_recorrer(abb, INORDEN, array, 10) == 7, "Recorrer en INORDEN con un array de mayor tamaño que el abb guarda solo los elementos del arbol");
	pa2m_afirmar(array[7] == NULL && array[8] == NULL && array[9] == NULL, "No se guardan elementos extra");
	
	pa2m_afirmar(abb_recorrer(abb, PREORDEN, array, 10) == 7, "Recorrer en PREORDEN con un array de mayor tamaño que el abb guarda solo los elementos del arbol");
	pa2m_afirmar(array[7] == NULL && array[8] == NULL && array[9] == NULL, "No se guardan elementos extra");

	abb_destruir(abb);
}

void abb_null_tiene_tamanio_0()
{
	pa2m_afirmar(abb_tamanio(NULL) == 0, "Un abb NULL tiene tamaño 0");
}

void abb_null_esta_vacio()
{
	pa2m_afirmar(abb_vacio(NULL) == true, "Un abb NULL esta vacio");
}

void destruir_un_arbol_con_elementos_no_pierde_memoria()
{
	abb_t *abb = abb_crear(comparar_enteros);
	int elementos[7] = {24,345,12,99,1,15,10};

	for(int i=0; i<7; i++)
		abb_insertar(abb, elementos+i);

	pa2m_afirmar(true, "Prueba del destructor normal (no debería perder memoria)");

	abb_destruir(abb);
}

void destruir_todos_con_destructor_null_no_destruye_elementos()
{
	abb_t *abb = abb_crear(comparar_enteros);
	int *elementos = malloc(7 * sizeof(int));

	for(int i=0; i<7; i++){
		elementos[i] = i%2 == 0 ? (-i-1) * 2 : (i+1)*2;
		abb_insertar(abb, elementos+i);
	}

	pa2m_afirmar(true, "Prueba de destruir todo con destructor NULL (no debería perder memoria ni destruir elementos)");

	abb_destruir_todo(abb, NULL);

	elementos[0] = 321;

	free(elementos);
}

void destruir_todos_con_destructor_no_null_no_pierde_memoria()
{
	abb_t *abb = abb_crear(comparar_enteros);
	int **elementos = malloc(4 * sizeof(int *));

	for(int i=0; i<4; i++){
		elementos[i] = malloc(sizeof(int));
		*elementos[i] = (i%2 == 0 ? (-i-1) * 2 : (i+1)*2);
		abb_insertar(abb, elementos[i]);
	}

	pa2m_afirmar(true, "Prueba de destruir todo con destructor no NULL (no debería perder memoria)");

	abb_destruir_todo(abb, free);

	free(elementos);
}

void destruir_con_abb_null_no_causa_errores()
{
	pa2m_afirmar(true, "Prueba de destruir un abb NULL (no debería causar errores)");
	abb_destruir(NULL);
}

int main()
{
	pa2m_nuevo_grupo("<- (: Pruebas de ABB :) ->");
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
	no_puedo_quitar_de_un_abb_vacio();
	no_puedo_quitar_un_elemento_que_no_existe_en_un_abb();
	quitar_la_raiz_en_un_abb_con_un_solo_elemento_deja_al_abb_vacio_y_con_tamanio_0();
	quitar_un_nodo_con_hijo_derecho_actualiza_correctamente_los_nodos_y_el_tamanio();
	quitar_un_nodo_con_hijo_izquierdo_actualiza_correctamente_los_nodos_y_el_tamanio();
	quitar_un_nodo_con_hijos_a_ambos_lados_actualiza_correctamente_los_nodos_y_el_tamanio();
	quitar_la_raiz_actualiza_correctamente_el_nodo_raiz();

	pa2m_nuevo_grupo("Pruebas de Busqueda");
	no_puedo_buscar_en_abb_nulo();
	buscar_un_elemento_que_no_existe_en_el_abb_devuelve_null();
	buscar_un_elemento_existente_en_el_arbol_devuelve_el_elemento();
	buscar_raiz_de_un_arbol_con_un_elemento_devuelve_el_elemento_de_la_raiz();

	pa2m_nuevo_grupo("Inserción, borrado y búsqueda sobre el mismo árbol");
	buscar_un_elemento_luego_de_borrar_otro_encuentra_el_elemento();
	buscar_un_elemento_recien_insertado_encuentra_el_elemento();
	insertar_luego_de_borrar_varios_elementos_actualiza_correctamente_el_arbol();
	buscar_luego_borrar_e_insertar_varios_elementos_encuentra_el_elemento();

	pa2m_nuevo_grupo("Pruebas de iterador interno");
	no_puedo_usar_el_iterador_interno_con_arbol_null();
	no_puedo_usar_el_iterador_interno_con_funcion_null();
	iterador_interno_de_un_arbol_vacio_invoca_a_la_funcion_0_veces();
	con_cada_elemento_con_recorrido_postorden_hasta_encontrar_el_10_invoca_a_la_funcion_una_sola_vez();
	con_cada_elemento_con_recorrido_postorden_recorre_los_elementos_correctos_hasta_encontrar_el_10();
	con_cada_elemento_con_recorrido_preorden_hasta_encontrar_el_10_invoca_a_la_funcion_cuatro_veces();
	con_cada_elemento_con_recorrido_preorden_recorre_los_elementos_correctos_hasta_encontrar_el_10();
	con_cada_elemento_con_recorrido_inorden_hasta_encontrar_el_10_invoca_a_la_funcion_dos_veces();
	con_cada_elemento_con_recorrido_inorden_recorre_los_elementos_correctos_hasta_encontrar_el_10();
	
	pa2m_nuevo_grupo("Pruebas de recorrer");
	recorrer_con_abb_nulo_no_hace_nada();
	recorrer_con_array_nulo_no_hace_nada();
	recorrer_con_tamanio_array_0_no_hace_nada();
	recorrer_un_abb_con_postorden_guarda_la_cantidad_de_elementos_indicada_en_el_orden_correcto();
	recorrer_un_abb_con_preorden_guarda_la_cantidad_de_elementos_indicada_en_el_orden_correcto();
	recorrer_un_abb_con_inorden_guarda_la_cantidad_de_elementos_indicada_en_el_orden_correcto();
	los_recorridos_de_un_abb_con_un_array_de_mayor_tamanio_que_el_abb_solo_guardan_los_elementos_del_abb();

	pa2m_nuevo_grupo("Pruebas de tamaño y vacio con abb NULL");
	abb_null_tiene_tamanio_0();
	abb_null_esta_vacio();

	pa2m_nuevo_grupo("Pruebas de destructores (no deberían perder memoria)");
	destruir_un_arbol_con_elementos_no_pierde_memoria();
	destruir_todos_con_destructor_null_no_destruye_elementos();
	destruir_todos_con_destructor_no_null_no_pierde_memoria();
	destruir_con_abb_null_no_causa_errores();

	return pa2m_mostrar_reporte();
}
