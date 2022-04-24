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

void puedo_insertar_un_elemento_null_en_la_lista_y_se_actualiza_el_tamanio_el_incio_y_el_fin()
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

void insertar_en_lista_con_mas_de_un_elemento_actualiza_el_fin_y_el_tamanio()
{
	lista_t *lista = lista_crear();
	char elementos[3] = {1, 2, 3};

	lista_insertar(lista, elementos+0);
	lista_insertar(lista, elementos+1);
	lista_insertar(lista, elementos+2);

	char elemento_final = 55;

	pa2m_afirmar(lista_insertar(lista, &elemento_final)==lista, "Puedo insertar en una lista con más de un elemento");
	pa2m_afirmar(lista_ultimo(lista)==&elemento_final, "El ultimo elemento es el insertado");
	pa2m_afirmar(lista_tamanio(lista)==4, "La lista tiene tamaño 4");

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

	pa2m_afirmar(lista->nodo_fin->elemento==elementos+3, "Quitar mas de un elemento actualiza el nodo final correctamente");
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

int main() {
	pa2m_nuevo_grupo("Pruebas de creacion de lista");
	crear_lista_devuelve_una_lista_vacia_de_tamanio_0_y_su_nodo_inicio_y_fin_son_null();

	pa2m_nuevo_grupo("Pruebas de insercion en lista");
	no_puedo_insertar_un_elemento_en_una_lista_null();
	insertar_en_lista_vacia_actualiza_el_tamanio_el_inicio_y_el_fin();
	puedo_insertar_un_elemento_null_en_la_lista_y_se_actualiza_el_tamanio_el_incio_y_el_fin();
	insertar_en_lista_con_un_elemento_actualiza_el_fin_y_no_altera_el_incio();
	insertar_en_lista_con_mas_de_un_elemento_actualiza_el_fin_y_el_tamanio();
	
	pa2m_nuevo_grupo("Pruebas de quitar elementos");
	quitar_con_un_elemento_devuelve_el_elemento_y_actualiza_el_primero_el_ultimo_y_el_tamanio();
	quitar_en_lista_con_dos_elementos_actualiza_el_tamanio_y_el_incio_y_fin_son_iguales();
	quitar_mas_de_un_elemento_actualiza_el_tamanio_y_el_fin();
	no_puedo_quitar_elemento_en_lista_null();
	no_puedo_quitar_elemento_en_lista_vacia();
	// ();
	// ();
	// ();

	return pa2m_mostrar_reporte();
}
