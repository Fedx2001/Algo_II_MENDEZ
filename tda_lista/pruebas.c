#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2mm.h"

void crear_lista_devuelve_una_lista_vacia_de_tamanio_0_y_su_nodo_inicio_y_fin_son_null()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista!=NULL, "Puedo crear una lista");
	pa2m_afirmar(lista_vacia(lista)==true, "La lista creada esta vacia");
	pa2m_afirmar(lista_tamanio(lista)==0, "El tamaño de la lista es 0");
	pa2m_afirmar(lista_primero(lista)==NULL, "El nodo inicio es NULL");
	pa2m_afirmar(lista_ultimo(lista)==NULL, "El nodo final es NULL");

	lista_destruir(lista);
}

void no_puedo_insertar_un_elemento_en_una_lista_null()
{
	int elemento = 5;

	pa2m_afirmar(lista_insertar(NULL, &elemento)==NULL, "No puedo insertar en una lista nula");
}

void insertar_en_lista_vacia_actualiza_el_tamanio_el_inicio_y_el_fin()
{
	lista_t *lista = lista_crear();
	int elemento = 5;

	pa2m_afirmar(lista_insertar(lista, &elemento)==lista, "Puedo insertar un elemento en una lista vacia");
	pa2m_afirmar(lista_tamanio(lista)==1, "La lista tiene tamaño 1");
	pa2m_afirmar(lista_primero(lista)==&elemento, "El primer elemento es el insertado");
	pa2m_afirmar(lista_primero(lista)==&elemento, "El ultimo elemento es el insertado");
	pa2m_afirmar(lista_primero(lista)==lista_ultimo(lista), "El primero y el ultimo son el mismo");

	lista_destruir(lista);
}

void puedo_insertar_un_elemento_null_en_la_lista_y_se_actualizan_el_tamanio_el_incio_y_el_fin()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_insertar(lista, NULL)==lista, "Puedo insertar un elemento NULL");
	pa2m_afirmar(lista_tamanio(lista)==1, "La lista tiene tamaño 1");
	pa2m_afirmar(lista_primero(lista)==NULL, "El primer elemento es NULL");
	pa2m_afirmar(lista_ultimo(lista)==NULL, "El ultimo elemento es NULL");

	lista_destruir(lista);
}

void insertar_en_lista_con_un_elemento_actualiza_el_fin_y_no_altera_el_incio()
{
	lista_t *lista = lista_crear();
	int primer_elemento = 1;

	lista_insertar(lista, &primer_elemento);

	int ultimo_elemento = 1000;

	pa2m_afirmar(lista_insertar(lista, &ultimo_elemento)==lista, "Puedo insertar en una lista con un solo elemento");
	pa2m_afirmar(lista_primero(lista)==&primer_elemento, "El primer elemento sigue siendo el mismo");
	pa2m_afirmar(lista_ultimo(lista)==&ultimo_elemento, "El ultimo elemento es el insertado");
	pa2m_afirmar(lista_tamanio(lista)==2, "La lista tiene tamaño 2");

	lista_destruir(lista);
}

void insertar_en_lista_con_mas_de_un_elemento_actualiza_el_fin()
{
	lista_t *lista = lista_crear();
	char elementos[3] = {1, 2, 3};

	lista_insertar(lista, elementos+0);
	lista_insertar(lista, elementos+1);
	lista_insertar(lista, elementos+2);

	char elemento_final = 55;

	pa2m_afirmar(lista_insertar(lista, &elemento_final)==lista, "Puedo insertar en una lista con 3 elementos");
	pa2m_afirmar(lista_ultimo(lista)==&elemento_final, "El ultimo elemento es el insertado");

	lista_destruir(lista);
}

void quitar_con_un_elemento_devuelve_el_elemento_y_actualiza_el_primero_el_ultimo_y_el_tamanio()
{
	lista_t *lista = lista_crear();
	char elemento = 1;
	lista_insertar(lista, &elemento);

	pa2m_afirmar(lista_quitar(lista)==&elemento, "Quitar en una lista de tamaño 1 devuelve el elemento");
	pa2m_afirmar(lista_primero(lista)==NULL, "El primer elemento luego de quitar es NULL");
	pa2m_afirmar(lista_ultimo(lista)==NULL, "El ultimo lemento luego de quitar es NULL");
	pa2m_afirmar(lista_tamanio(lista)==0, "El tamanio de la lista es 0");
	pa2m_afirmar(lista_vacia(lista)==true, "La lista esta vacia");

	lista_destruir(lista);
}

void quitar_en_lista_con_dos_elementos_actualiza_el_tamanio_y_el_incio_y_fin_son_iguales()
{
	lista_t *lista = lista_crear();
	int elemento1 = 100;
	int elemento2 = 200;

	lista_insertar(lista, &elemento1);
	lista_insertar(lista, &elemento2);

	pa2m_afirmar(lista_quitar(lista)==&elemento2, "Quitar en una lista de tamaño 2 devuelve el segundo elemento");
	pa2m_afirmar(lista->nodo_fin==lista->nodo_inicio, "El incio y el fin son el mismo luego de quitar");
	pa2m_afirmar(lista_tamanio(lista)==1, "El tamaño de la lista es 1 luego de quitar");

	lista_destruir(lista);
}

void quitar_mas_de_un_elemento_actualiza_el_tamanio_y_el_fin()
{
	lista_t *lista = lista_crear();
	int elementos[6] = {1, 2, 3, 4, 5, 200};
	for(int i=0; i<6; i++)
		lista_insertar(lista, elementos+i);

	lista_quitar(lista);
	lista_quitar(lista);

	pa2m_afirmar(lista->nodo_fin->elemento==elementos+3, "Quitar mas de un elemento actualiza el final");
	pa2m_afirmar(lista_tamanio(lista)==4, "El tamaño se actualiza correctamente");

	lista_destruir(lista);
}

void no_puedo_quitar_elemento_en_lista_null()
{
	pa2m_afirmar(lista_quitar(NULL)==NULL, "No puedo quitar un elemento de una lista NULL");
}

void no_puedo_quitar_elemento_en_lista_vacia()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_quitar(lista)==NULL, "No puedo quitar un elemento de una lista vacia");

	lista_destruir(lista);
}

void puedo_insertar_en_la_posicion_1_de_una_lista_vacia()
{
	lista_t *lista = lista_crear();
	char elemento = 123;
	pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento, 1)==lista, "Puedo insertar en la posicion 1 de una lista vacia");
	pa2m_afirmar(lista_primero(lista)==&elemento && lista_ultimo(lista)==&elemento, "El inicio y fin de la lista son el elemento insertado");
	lista_destruir(lista);
}

void insertar_en_la_posicion_2_de_una_lista_con_3_elementos_no_cambia_el_fin()
{
	lista_t *lista = lista_crear();
	int elementos[4] = {0, 1, 2, 3};
	for(int i=0; i<3; i++)
		lista_insertar(lista, elementos+i);

	pa2m_afirmar(lista_insertar_en_posicion(lista, elementos+3, 2)==lista, "Puedo insertar en la posicion 2 de una lista con 3 elementos");
	pa2m_afirmar(lista->nodo_fin->elemento==elementos+2, "El fin sigue siendo el mismo");

	lista_destruir(lista);
}

void insertar_en_la_posicion_5000_de_una_lista_con_2_elementos_inserta_al_final()
{
	lista_t *lista = lista_crear();
	int elementos[3] = {0, 1, 2};
	for(int i=0; i<2; i++)
		lista_insertar(lista, elementos+i);

	pa2m_afirmar(lista_insertar_en_posicion(lista, elementos+2, 5000)==lista, "Puedo insertar en la posicion 5000 de una lista con 2 elementos");
	pa2m_afirmar(lista->nodo_fin->elemento==elementos+2, "El elemento se inserta al final");

	lista_destruir(lista);
}

void no_puedo_insertar_en_una_posicion_de_una_lista_null()
{
	int elemento = 4;
	pa2m_afirmar(lista_insertar_en_posicion(NULL, &elemento, 1)==NULL, "No puedo insertar en posicion de lista NULL");
}

void no_puedo_quitar_de_posicion_de_una_lista_null()
{
	pa2m_afirmar(lista_quitar_de_posicion(NULL, 1)==NULL, "No puedo quitar de posicion de una lista NULL");
}
void no_puedo_quitar_de_posicion_de_una_lista_vacia()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_quitar_de_posicion(lista, 0)==NULL, "No puedo quitar de posicion de una lista vacia");
	lista_destruir(lista);
}

void quitar_de_posicion_0_de_una_lista_con_1_elemento_deja_la_lista_vacia_y_devuelve_el_elemento()
{
	lista_t *lista = lista_crear();
	char *elemento = "Hoola";
	lista_insertar(lista, elemento);

	pa2m_afirmar(lista_quitar_de_posicion(lista, 0)==elemento, "Quitar de posicion 0 de una lista con 1 elemento devuelve el elemento");
	pa2m_afirmar(lista_vacia(lista), "La lista esta vacia luego de quitar");

	lista_destruir(lista);
}

void quitar_de_posicion_5000_en_una_lista_con_1_elemento_quita_el_final_y_deja_la_lista_vacia()
{
	lista_t *lista = lista_crear();
	char *elemento = "ALGORITMOS!!!!";
	lista_insertar(lista, elemento);

	pa2m_afirmar(lista_quitar_de_posicion(lista, 5000)==elemento, "Quitar de posicion 5000 de una lista con 1 elemento devuelve el elemento");
	pa2m_afirmar(lista_vacia(lista), "La lista esta vacia luego de quitar");

	lista_destruir(lista);
}

void quitar_de_posicion_0_de_una_lista_con_2_elementos_devuelve_el_primer_elemento_y_actualiza_el_inicio()
{
	lista_t *lista = lista_crear();
	char *elementos[2] = {"ALGORITMOS Y", " PROGRAMACION!!!"};
	lista_insertar(lista, elementos+0);
	lista_insertar(lista, elementos+1);

	pa2m_afirmar(lista_quitar_de_posicion(lista, 0)==elementos+0, "Quitar de posicion 0 de una lista con 2 elementos devuelve el primer elemento");
	pa2m_afirmar(lista_primero(lista)==elementos+1, "El inicio se actualiza correctamente");

	lista_destruir(lista);
}

void no_existe_elemento_en_posicion_4_de_una_lista_con_3_elementos()
{
	lista_t *lista = lista_crear();
	char *elementos[3] = {"ALGORITMOS Y", " ALGOritmos", "¿Te importa este string? a mi no"};
	for(int i=0; i<3; i++)
		lista_insertar(lista, elementos+i);
	
	pa2m_afirmar(lista_elemento_en_posicion(lista, 4)==NULL, "No existe elemento en posicion 4 de una lista con 3 elementos");

	lista_destruir(lista);
}

void tras_quitar_el_ultimo_elemento_de_una_lista_con_4_elementos_no_existe_elemento_en_posicion_3()
{
	lista_t *lista = lista_crear();
	char *elementos[4] = {"Chrono Trigger", "Peaceful Days", "Boss Battle 1", "Corridors of Time"};
	for(int i=0; i<4; i++)
		lista_insertar(lista, elementos+i);
	
	pa2m_afirmar(lista_quitar(lista)==elementos+3, "Quité el ultimo elemento de una lista con 4 elementos");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 3)==NULL, "Luego de quitar, no existe elemento en la posicion 3");

	lista_destruir(lista);
}

void no_existe_elemento_en_posicion_0_de_una_lista_vacia()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0)==NULL, "No existe elemento en posicion 0 de una lista vacia");
	lista_destruir(lista);
}

void no_existe_elemento_en_posicion_0_de_una_lista_null()
{
	pa2m_afirmar(lista_elemento_en_posicion(NULL, 0)==NULL, "No existe elemento en posicion 0 de una lista NULL");
}

/*
* Pruebas de iterador externo
*/
void un_iterador_externo_null_no_tiene_siguiente()
{
	pa2m_afirmar(lista_iterador_tiene_siguiente(NULL)==false, "El iterador externo NULL no tiene siguiente");
}

void crear_un_iterador_externo_de_lista_null_es_un_error()
{
	pa2m_afirmar(lista_iterador_crear(NULL)==NULL, "Crear un iterador de una lista NULL es un error");
}

void iterador_en_ultimo_elemento_no_tiene_siguiente()
{
	lista_t *lista = lista_crear();
	char *elemento = "To Zanarkand"; 
	lista_insertar(lista, elemento);
	
	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void iterador_de_lista_vacia_no_tiene_siguiente_y_su_elemento_es_null();

void una_lista_null_esta_vacia()
{
	pa2m_afirmar(lista_vacia(NULL)==true, "Una lista NULL está vacía");
}

void lista_null_tiene_tamanio_0()
{
	pa2m_afirmar(lista_tamanio(NULL)==0, "Una lista NULL tiene tamaño 0");
}

void insertar_en_posicion_luego_de_quitar_de_posicion_actualiza_el_tamanio_correctamente()
{
	lista_t *lista = lista_crear();
	int elementos[1000];
	for(int i=0; i<1000; i++) {
		elementos[i] = i+1;
		lista_insertar(lista, elementos+i);
	}

	int elemento = 1001;

	pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento, 15)==lista, "Puedo insertar en la posicion 15 en una lista de 1000 elementos");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 15)==&elemento, "El elemento insertado esta en la posicion correcta");
	pa2m_afirmar(lista_tamanio(lista)==1001, "El tamaño de la lista ahora es 1001");
	pa2m_afirmar(lista_quitar_de_posicion(lista, 15)==&elemento, "Quitar el elemento de la posicion 15 me devuelve el elemento");
	pa2m_afirmar(lista_tamanio(lista)==1000, "El tamaño de la lista es 1000 luego de quitar");
	for(int i=0; i<3; i++)
		lista_quitar_de_posicion(lista, (size_t)i*2);

	pa2m_afirmar(lista_tamanio(lista)==997, "El tamaño de la lista es 997 luego de quitar 3 elementos de posiciones");

	lista_destruir(lista);
}

int main() {
	pa2m_nuevo_grupo("Pruebas de TDA Lista");
	pa2m_nuevo_grupo("Pruebas de creacion de lista");
	crear_lista_devuelve_una_lista_vacia_de_tamanio_0_y_su_nodo_inicio_y_fin_son_null();

	pa2m_nuevo_grupo("Pruebas de insertar al final");
	no_puedo_insertar_un_elemento_en_una_lista_null();
	insertar_en_lista_vacia_actualiza_el_tamanio_el_inicio_y_el_fin();
	puedo_insertar_un_elemento_null_en_la_lista_y_se_actualizan_el_tamanio_el_incio_y_el_fin();
	insertar_en_lista_con_un_elemento_actualiza_el_fin_y_no_altera_el_incio();
	insertar_en_lista_con_mas_de_un_elemento_actualiza_el_fin();
	
	pa2m_nuevo_grupo("Pruebas de quitar al final");
	no_puedo_quitar_elemento_en_lista_null();
	no_puedo_quitar_elemento_en_lista_vacia();
	quitar_con_un_elemento_devuelve_el_elemento_y_actualiza_el_primero_el_ultimo_y_el_tamanio();
	quitar_en_lista_con_dos_elementos_actualiza_el_tamanio_y_el_incio_y_fin_son_iguales();
	quitar_mas_de_un_elemento_actualiza_el_tamanio_y_el_fin();

	pa2m_nuevo_grupo("Pruebas de insertar en posicion");
	no_puedo_insertar_en_una_posicion_de_una_lista_null();
	puedo_insertar_en_la_posicion_1_de_una_lista_vacia();
	insertar_en_la_posicion_2_de_una_lista_con_3_elementos_no_cambia_el_fin();
	insertar_en_la_posicion_5000_de_una_lista_con_2_elementos_inserta_al_final();

	pa2m_nuevo_grupo("Pruebas de quitar de posicion");
	no_puedo_quitar_de_posicion_de_una_lista_null();
	no_puedo_quitar_de_posicion_de_una_lista_vacia();
	quitar_de_posicion_0_de_una_lista_con_1_elemento_deja_la_lista_vacia_y_devuelve_el_elemento();
	quitar_de_posicion_5000_en_una_lista_con_1_elemento_quita_el_final_y_deja_la_lista_vacia();
	quitar_de_posicion_0_de_una_lista_con_2_elementos_devuelve_el_primer_elemento_y_actualiza_el_inicio();

	pa2m_nuevo_grupo("Pruebas de elemento en posicion");
	no_existe_elemento_en_posicion_4_de_una_lista_con_3_elementos();
	tras_quitar_el_ultimo_elemento_de_una_lista_con_4_elementos_no_existe_elemento_en_posicion_3();
	no_existe_elemento_en_posicion_0_de_una_lista_vacia();
	no_existe_elemento_en_posicion_0_de_una_lista_null();

	pa2m_nuevo_grupo("Pruebas de iterador externo");
	un_iterador_externo_null_no_tiene_siguiente();
	crear_un_iterador_externo_de_lista_null_es_un_error();
	iterador_en_ultimo_elemento_no_tiene_siguiente();
	iterador_de_lista_vacia_no_tiene_siguiente_y_su_elemento_es_null();

	pa2m_nuevo_grupo("Pruebas de iterador interno");

	pa2m_nuevo_grupo("Pruebas de buscar elemento");


	//pa2m_nuevo_grupo("Pruebas de destruir y destruir todo");
	//destruir_todo_de_lista_null_no_hace_nada();
	//lista_destruir_no_pierde_memoria();

	pa2m_nuevo_grupo("Pruebas de tamaño y lista vacia");
	una_lista_null_esta_vacia();
	lista_null_tiene_tamanio_0();
	insertar_en_posicion_luego_de_quitar_de_posicion_actualiza_el_tamanio_correctamente();

	pa2m_nuevo_grupo("Pruebas de TDA Cola");
	

	pa2m_nuevo_grupo("Pruebas de TDA Pila");


	return pa2m_mostrar_reporte();
}
