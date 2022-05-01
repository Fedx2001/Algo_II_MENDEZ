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

void un_iterador_externo_null_no_tiene_siguiente()
{
	pa2m_afirmar(lista_iterador_tiene_siguiente(NULL)==false, "Un iterador externo NULL no tiene siguiente");
}

void crear_un_iterador_externo_de_lista_null_es_un_error()
{
	pa2m_afirmar(lista_iterador_crear(NULL)==NULL, "Crear un iterador de una lista NULL es un error");
}

void iterador_en_ultimo_elemento_tiene_siguiente_y_el_elemento_actual_es_el_elemento()
{
	lista_t *lista = lista_crear();
	char *elemento = "To Zanarkand";
	lista_insertar(lista, elemento);
	lista_iterador_t *iterador = lista_iterador_crear(lista);

	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador)==true, "El iterador en el ultimo elemento de la lista no tiene siguiente");
	pa2m_afirmar(lista_iterador_elemento_actual(iterador)==elemento, "El elemento actual es el elemento");

	lista_iterador_destruir(iterador);

	lista_destruir(lista);
}

void iterador_de_lista_vacia_no_tiene_siguiente_y_su_elemento_es_null()
{
	lista_t *lista = lista_crear();
	lista_iterador_t *iterador = lista_iterador_crear(lista);

	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador)==false, "El iterador de una lista vacia no tiene siguiente");
	pa2m_afirmar(lista_iterador_elemento_actual(iterador)==NULL, "El elemento actual del iterador de una lista NULL es NULL");

	lista_destruir(lista);
	lista_iterador_destruir(iterador);
}

void puedo_recorrer_todos_los_elementos_de_la_lista_con_un_iterador_externo()
{
	lista_t *lista = lista_crear();

	char *elementos[5] = {"Lena Raine", "Nobuo Uematsu", "Yasunori Mitsuda", "Matt Uelmen", "Toby Fox"};
	for(int i=0; i<5; i++)
		lista_insertar(lista, elementos+i);

	lista_iterador_t *iterador = NULL;
	int contador = 0;

	for(iterador = lista_iterador_crear(lista);
		lista_iterador_tiene_siguiente(iterador);
		lista_iterador_avanzar(iterador))
			contador++;

	pa2m_afirmar(lista_tamanio(lista)==contador, "Puedo recorrer todos los elementos de la lista con el iterador externo");

	lista_iterador_destruir(iterador);

	lista_destruir(lista);
}

void no_puedo_usar_iterador_interno_con_funcion_null()
{
	lista_t *lista = lista_crear();
	int contexto = 10;

	pa2m_afirmar(lista_con_cada_elemento(lista, NULL, &contexto)==0, "No puedo usar el interador interno con funcion NULL");

	lista_destruir(lista);
}


bool _es_par(void *numero, void *contexto)
{
	return *(int *)numero%2==0 ? true : false;
}

void no_puedo_usar_iterador_interno_con_lista_null()
{
	int contexto = 2;
	pa2m_afirmar(lista_con_cada_elemento(NULL, _es_par, &contexto)==0, "No puedo usar el interador interno con lista NULL");

}

void puedo_usar_iterador_interno_con_contexto_null()
{
	lista_t *lista = lista_crear();
	int elementos[3] = {2, 4, 6};
	for(int i=0; i<2; i++)
		lista_insertar(lista, elementos+i);

	pa2m_afirmar(lista_con_cada_elemento(lista, _es_par, NULL)!=0, "Puedo usar el interador interno con contexto NULL");

	lista_destruir(lista);
}

void puedo_recorrer_toda_la_lista_con_iterador_interno()
{
	lista_t *lista = lista_crear();
	int elementos[3] = {2, 4, 6};
	for(int i=0; i<3; i++)
		lista_insertar(lista, elementos+i);

	pa2m_afirmar(lista_con_cada_elemento(lista, _es_par, NULL)==3, "Puedo recorrer toda la lista con el iterador interno");

	lista_destruir(lista);
}

bool seguir_iterando(void *elemento, void *contexto)
{
	if(*(int *)elemento == *(int *)contexto)
		return false;
	return true;
}

void puedo_recorrer_3_elementos_de_una_lista_de_10_elementos_con_iterador_interno()
{
	lista_t *lista = lista_crear();
	int elementos[10] = {2,4,6,7,9,10,13,15,18,20};
	int contexto = 6;

	for(int i=0; i<10; i++) {
		lista_insertar(lista, elementos+i);
	}

	pa2m_afirmar(lista_con_cada_elemento(lista, seguir_iterando, &contexto)==3, "Buscar el tercer elemento de la lista itera 3 elementos");

	lista_destruir(lista);
}

void recorrer_lista_vacia_con_iterador_interno_devuelve_0_elementos_iterados()
{
	lista_t *lista = lista_crear();
	int contexto = 6;

	pa2m_afirmar(lista_con_cada_elemento(lista, seguir_iterando, &contexto)==0, "Recorrer una lista vacia con el iterador interno devuelve 0 elementos iterados");

	lista_destruir(lista);
}

int _es_contexto(void *elemento, void *contexto)
{
	return *(int *)elemento == *(int *)contexto ? 0 : -1;
}

void no_puedo_buscar_un_elemento_en_una_lista_null()
{
	int contexto = 6;
	pa2m_afirmar(lista_buscar_elemento(NULL, _es_contexto, &contexto)==NULL, "No puedo buscar un elemento en una lista NULL");
}

void no_puedo_buscar_un_elemento_en_una_lista_con_comparador_null()
{
	int contexto = 6;
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_buscar_elemento(lista, NULL, &contexto)==NULL, "No puedo buscar un elemento en una lista con comparador NULL");

	lista_destruir(lista);
}

void buscar_elemento_en_lista_vacia_devuelve_null()
{
	int contexto = 6;
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_buscar_elemento(lista, _es_contexto, &contexto)==NULL, "Buscar un elemento en una lista vacia devuelve NULL");

	lista_destruir(lista);
}

void buscar_elemento_inexistente_en_lista_devuelve_null()
{
	int a_buscar = 1;
	lista_t *lista = lista_crear();

	int elementos[10] = {2,4,6,7,9,10,13,15,18,20};
	for(int i=0; i<10; i++) {
		lista_insertar(lista, elementos+i);
	}

	pa2m_afirmar(lista_buscar_elemento(lista, _es_contexto, &a_buscar)==NULL, "Buscar un elemento inexistente en la lista devuelve NULL");

	lista_destruir(lista);
}

void buscar_elemento_existente_en_lista_devuelve_el_elemento()
{
	int a_buscar = 7;
	lista_t *lista = lista_crear();

	int elementos[10] = {2,4,6,7,9,10,13,15,18,20};
	for(int i=0; i<10; i++) {
		lista_insertar(lista, elementos+i);
	}

	pa2m_afirmar(lista_buscar_elemento(lista, _es_contexto, &a_buscar)==elementos+3, "Buscar un elemento en la lista devuelve el elemento");

	lista_destruir(lista);
}

void una_lista_null_esta_vacia()
{
	pa2m_afirmar(lista_vacia(NULL)==true, "Una lista NULL está vacía");
}

void lista_null_tiene_tamanio_0()
{
	pa2m_afirmar(lista_tamanio(NULL)==0, "Una lista NULL tiene tamaño 0");
}

void insertar_en_posicion_y_quitar_de_posicion_actualizan_el_tamanio_correctamente()
{
	lista_t *lista = lista_crear();
	int elementos[500];
	for(int i=0; i<500; i++) {
		elementos[i] = i+1;
		lista_insertar(lista, elementos+i);
	}

	int elemento = 450;

	pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento, 69)==lista, "Puedo insertar en la posicion 69 en una lista de 500 elementos");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 69)==&elemento, "El elemento insertado esta en la posicion correcta");
	pa2m_afirmar(lista_tamanio(lista)==501, "El tamaño de la lista ahora es 501");
	pa2m_afirmar(lista_quitar_de_posicion(lista, 69)==&elemento, "Quitar el elemento de la posicion 69 me devuelve el elemento");
	pa2m_afirmar(lista_tamanio(lista)==500, "El tamaño de la lista es 500 luego de quitar");

	for(size_t i=0; i<500; i++) {
		lista_quitar(lista);
	}

	pa2m_afirmar(lista_vacia(lista), "Quitar todos los elementos deja la lista vacia");
	pa2m_afirmar(lista_tamanio(lista)==0, "La lista es de tamaño 0");

	lista_destruir(lista);
}

void destruir_todo_con_funcion_null_no_destruye_elementos()
{
	int *elemento = malloc(sizeof(int));
	*elemento = 123123;

	lista_t *lista = lista_crear();
	lista_insertar(lista, elemento);

	lista_destruir_todo(lista, NULL);

	pa2m_afirmar(elemento, "Destruir todo con funcion NULL no destruye elementos");

	free(elemento);
}

void puedo_crear_una_cola_y_su_frente_es_null()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola!=NULL, "Puedo crear una cola");
	pa2m_afirmar(cola_frente(cola)==NULL, "El frente de la cola es NULL");

	cola_destruir(cola);
}

void una_cola_recien_creada_esta_vacia()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola_vacia(cola), "Una cola recien creada esta vacia");

	cola_destruir(cola);
}

void no_puedo_encolar_en_una_cola_null()
{
	int elemento = 0;
	pa2m_afirmar(cola_encolar(NULL, &elemento)==NULL, "No puedo encolar en una cola NULL");
}

void puedo_encolar_un_elemento_null()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola_encolar(cola, NULL), "Puedo encolar un elemento NULL en una cola");

	cola_destruir(cola);
}

void puedo_encolar_en_una_cola_vacia_y_el_frente_es_el_correcto()
{
	cola_t *cola = cola_crear();
	int elemento = 10123;

	pa2m_afirmar(cola_encolar(cola, &elemento)==cola, "Puedo encolar en una cola vacia");

	pa2m_afirmar(cola_frente(cola)==&elemento, "El frente es el correcto");

	cola_destruir(cola);
}

void encolar_varios_elementos_no_cambia_el_frente()
{
	cola_t *cola = cola_crear();
	char *elementos[5] = {"Frente", "B", "C", "D", "Fin"};
	for(int i=0; i<5; i++)
		cola_encolar(cola, elementos+i);

	pa2m_afirmar(cola_frente(cola)==elementos, "Encolar varios elementos no cambia el frente");

	cola_destruir(cola);
}

void no_puedo_desencolar_de_una_cola_null()
{
	pa2m_afirmar(cola_desencolar(NULL)==NULL, "No puedo desencolar de una cola NULL");
}

void no_puedo_desencolar_de_una_cola_vacia()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola_desencolar(cola)==NULL, "No puedo desencolar de una cola vacia");

	cola_destruir(cola);
}

void desencolar_devuelve_el_elemento_correcto()
{
	cola_t *cola = cola_crear();
	char *elementos[5] = {"Frente", "B", "C", "D", "Fin"};
	for(int i=0; i<5; i++)
		cola_encolar(cola, elementos+i);

	pa2m_afirmar(cola_desencolar(cola)==elementos, "Desencolar devuelve el primer elemento de la cola");

	cola_destruir(cola);
}

void desencolar_varios_elementos_actualiza_el_frente()
{
	cola_t *cola = cola_crear();
	char *elementos[5] = {"Frente", "B", "C", "D", "Fin"};

	for(int i=0; i<5; i++)
		cola_encolar(cola, elementos+i);

	cola_desencolar(cola);
	cola_desencolar(cola);
	cola_desencolar(cola);

	pa2m_afirmar(cola_frente(cola)==elementos+3, "Desencolar varios elementos actualiza el frente");

	cola_destruir(cola);
}

void desencolar_todos_los_elementos_deja_la_cola_vacia()
{
	cola_t *cola = cola_crear();
	char *elementos[5] = {"A", "B", "C", "D", "E"};

	for(int i=0; i<5; i++)
		cola_encolar(cola, elementos+i);

	for(int i=0; i<5; i++)
		cola_desencolar(cola);

	pa2m_afirmar(cola_vacia(cola), "Desencolar todos los elementos deja la lista vacia");
	pa2m_afirmar(cola_frente(cola)==NULL, "La cola no tiene frente");

	cola_destruir(cola);
}

void desencolar_devuelve_los_elementos_en_el_orden_correcto()
{
	cola_t *cola = cola_crear();
	char *elementos[6] = {"Algo", "ritmos", " ", "Y", " ", "Programacion"};
	bool elementos_estan_ordenados = true;

	for(int i=0; i<6; i++)
		cola_encolar(cola, elementos+i);

	for(int i=0; i<6; i++) {
		if(cola_desencolar(cola)!=elementos+i) {
			elementos_estan_ordenados = false;
			break;
		}
	}

	pa2m_afirmar(elementos_estan_ordenados, "Desencolar devuelve los elementos en el orden correcto");

	cola_destruir(cola);
}

void el_frente_de_una_cola_null_es_null()
{
	pa2m_afirmar(cola_frente(NULL)==NULL, "El frente de una cola NULL es NULL");
}

void el_frente_de_una_cola_vacia_es_null()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola_frente(cola)==NULL, "El frente de una cola vacia es NULL");

	cola_destruir(cola);
}

void encolar_y_desencolar_varios_elementos_actualiza_correctamente_el_frente()
{
	cola_t *cola = cola_crear();
	char *elementos[6] = {"Algo", "ritmos", "22222", "Y", "22222", "Programacion"};

	for(int i=0; i<6; i++)
		cola_encolar(cola, elementos+i);

	for(int i=0; i<3; i++)
		cola_desencolar(cola);

	pa2m_afirmar(cola_frente(cola)==elementos+3, "Desencolo 3 elementos de una cola con 6 elementos y el frente es el correcto");

	cola_encolar(cola, elementos);
	cola_encolar(cola, elementos+1);

	pa2m_afirmar(cola_frente(cola)==elementos+3, "Encolo 2 elementos y el frente no cambia");

	cola_destruir(cola);
}

void puedo_crear_una_pila_y_su_tope_es_null()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila!=NULL, "Puedo crear una pila");
	pa2m_afirmar(pila_tope(pila)==NULL, "El tope de la pila es NULL");

	pila_destruir(pila);
}

void una_pila_recien_creada_esta_vacia()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_vacia(pila), "Una pila recien creada esta vacia");

	pila_destruir(pila);
}

void no_puedo_apilar_en_una_pila_null()
{
	int elemento = 0;
	pa2m_afirmar(pila_apilar(NULL, &elemento)==NULL, "No puedo apilar en una pila NULL");
}

void puedo_apilar_un_elemento_null()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_apilar(pila, NULL)==pila, "Puedo apilar un elemento NULL");

	pila_destruir(pila);
}

void puedo_apilar_en_una_pila_vacia_y_el_tope_es_el_elemento()
{
	pila_t *pila = pila_crear();
	char letra = 'a';

	pila_apilar(pila, &letra);

	pa2m_afirmar(pila_tope(pila)==&letra, "Puedo apilar en una pila vacia y el tope es el elemento");

	pila_destruir(pila);
}

void apilar_varios_elementos_actualiza_correctamente_el_tope()
{
	pila_t *pila = pila_crear();
	char letras[10] = {'a', 'l', 'g', 'o', 'r', 'i', 't', 'm', 'o', 's'};

	for(int i=9; i>=0; i--)
		pila_apilar(pila, letras+i);

	pa2m_afirmar(pila_tope(pila)==letras, "Apilar varios elementos actualiza el tope");

	pila_destruir(pila);
}

void no_puedo_desapilar_de_una_pila_null()
{
	pa2m_afirmar(pila_desapilar(NULL)==NULL, "No puedo desapilar de una pila NULL");
}

void no_puedo_desapilar_de_una_pila_vacia()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_desapilar(pila)==NULL, "No puedo desapilar de una pila vacia");

	pila_destruir(pila);
}

void desapilar_de_una_pila_devuelve_el_elemento_y_actualiza_el_tope()
{
	pila_t *pila = pila_crear();
	char letras[10] = {'a', 'l', 'g', 'o', 'r', 'i', 't', 'm', 'o', 's'};

	for(int i=9; i>=0; i--)
		pila_apilar(pila, letras+i);

	pa2m_afirmar(pila_desapilar(pila)==letras, "Desapilar de una pila devuelve el elemento correcto");
	pa2m_afirmar(pila_tope(pila)==letras+1, "Se actualizo el tope al siguiente elemento");

	pila_destruir(pila);
}

void desapilar_varios_elementos_actualiza_el_tope_correctamente()
{
	pila_t *pila = pila_crear();
	char letras[10] = {'a', 'l', 'g', 'o', 'r', 'i', 't', 'm', 'o', 's'};

	for(int i=9; i>=0; i--)
		pila_apilar(pila, letras+i);

	for(int i=0; i<4; i++)
		pila_desapilar(pila);

	pa2m_afirmar(pila_tope(pila)==letras+4, "Desapilar varios elementos actualiza el tope al elemento correcto");

	pila_destruir(pila);
}

void desapilar_todos_los_elementos_deja_la_pila_vacia()
{
	pila_t *pila = pila_crear();
	char letras[10] = {'a', 'l', 'g', 'o', 'r', 'i', 't', 'm', 'o', 's'};

	for(int i=9; i>=0; i--)
		pila_apilar(pila, letras+i);

	for(int i=0; i<10; i++)
		pila_desapilar(pila);

	pa2m_afirmar(pila_vacia(pila), "Desapilar todos los elementos deja la pila vacia");
	pa2m_afirmar(pila_tope(pila)==NULL, "El tope de la pila es NULL");

	pila_destruir(pila);
}

void desapilar_devuelve_los_elementos_en_el_orden_correcto()
{
	pila_t *pila = pila_crear();
	char letras[15] = {'F', 'i', 'n', 'a', 'l', ' ', 'F', 'a', 'n', 't', 'a', 's', 'y', ' ', 'I'};
	bool elementos_estan_ordenados = true;

	for(int i=14; i>=0; i--)
		pila_apilar(pila, letras+i);

	for(int i=0; i<15; i++) {
		if(pila_desapilar(pila)!=letras+i)
			elementos_estan_ordenados = false;
	}

	pa2m_afirmar(elementos_estan_ordenados, "Desapilar devuelve los elementos en el orden correcto");

	pila_destruir(pila);
}

void el_tope_de_una_pila_null_es_null()
{
	pa2m_afirmar(pila_tope(NULL)==NULL, "El tope de una pila NULL es NULL");
}

void el_tope_de_una_pila_vacia_es_null()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_tope(pila)==NULL, "El tope de una pila vacia es NULL");

	pila_destruir(pila);
}

void apilar_y_desapilar_varios_elementos_actualiza_correctamente_el_tope()
{
	pila_t *pila = pila_crear();
	char *canciones[10] = {
		"Turnabout Squeeze", "Out of Tartarus", "Dr. Willy's Castle", 
		"To the Moon", "NOW'S YOUR CHANCE TO BE A", "Smart Race", 
		"Wake up, Get up, Get out there", "Prelude/Prologue (FF I)", 
		"Lucca's Theme", "Green Hill Zone"
	};

	for(int i=9; i>=0; i--)
		pila_apilar(pila, canciones+i);

	for(int i=0; i<4; i++) {
		pila_desapilar(pila);
	}

	pa2m_afirmar(pila_tope(pila)==canciones+4, "Desapilo 4 elementos de una pila con 10 elementos y el tope es el correcto");

	pila_apilar(pila, canciones+1);
	pila_apilar(pila, canciones+2);
	pila_apilar(pila, canciones);

	pa2m_afirmar(pila_tope(pila)==canciones, "Apilo 3 elementos y el nuevo tope es el correcto");

	pila_destruir(pila);
}

int main() {
	pa2m_nuevo_grupo("< PRUEBAS DE TDA LISTA >");
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
	iterador_en_ultimo_elemento_tiene_siguiente_y_el_elemento_actual_es_el_elemento();
	iterador_de_lista_vacia_no_tiene_siguiente_y_su_elemento_es_null();
	puedo_recorrer_todos_los_elementos_de_la_lista_con_un_iterador_externo();

	pa2m_nuevo_grupo("Pruebas de iterador interno");
	no_puedo_usar_iterador_interno_con_funcion_null();
	no_puedo_usar_iterador_interno_con_lista_null();
	puedo_usar_iterador_interno_con_contexto_null();
	puedo_recorrer_toda_la_lista_con_iterador_interno();
	puedo_recorrer_3_elementos_de_una_lista_de_10_elementos_con_iterador_interno();
	recorrer_lista_vacia_con_iterador_interno_devuelve_0_elementos_iterados();

	pa2m_nuevo_grupo("Pruebas de buscar elemento");
	no_puedo_buscar_un_elemento_en_una_lista_null();
	no_puedo_buscar_un_elemento_en_una_lista_con_comparador_null();
	buscar_elemento_en_lista_vacia_devuelve_null();
	buscar_elemento_inexistente_en_lista_devuelve_null();
	buscar_elemento_existente_en_lista_devuelve_el_elemento();

	pa2m_nuevo_grupo("Pruebas de tamaño y lista vacia");
	una_lista_null_esta_vacia();
	lista_null_tiene_tamanio_0();
	insertar_en_posicion_y_quitar_de_posicion_actualizan_el_tamanio_correctamente();

	pa2m_nuevo_grupo("Prueba de destruir todo");
	destruir_todo_con_funcion_null_no_destruye_elementos();

	pa2m_nuevo_grupo("< PRUEBAS DE TDA COLA >");
	pa2m_nuevo_grupo("Pruebas de creacion");
	puedo_crear_una_cola_y_su_frente_es_null();
	una_cola_recien_creada_esta_vacia();

	pa2m_nuevo_grupo("Pruebas de encolar");
	no_puedo_encolar_en_una_cola_null();
	puedo_encolar_en_una_cola_vacia_y_el_frente_es_el_correcto();
	encolar_varios_elementos_no_cambia_el_frente();
	puedo_encolar_un_elemento_null();

	pa2m_nuevo_grupo("Pruebas de desencolar");
	no_puedo_desencolar_de_una_cola_null();
	no_puedo_desencolar_de_una_cola_vacia();
	desencolar_devuelve_el_elemento_correcto();
	desencolar_varios_elementos_actualiza_el_frente();
	desencolar_todos_los_elementos_deja_la_cola_vacia();
	desencolar_devuelve_los_elementos_en_el_orden_correcto();

	pa2m_nuevo_grupo("Pruebas de ver frente");
	el_frente_de_una_cola_null_es_null();
	el_frente_de_una_cola_vacia_es_null();
	encolar_y_desencolar_varios_elementos_actualiza_correctamente_el_frente();

	pa2m_nuevo_grupo("< PRUEBAS DE TDA PILA >");
	pa2m_nuevo_grupo("Pruebas de creacion");
	puedo_crear_una_pila_y_su_tope_es_null();
	una_pila_recien_creada_esta_vacia();

	pa2m_nuevo_grupo("Pruebas de apilar");
	no_puedo_apilar_en_una_pila_null();
	puedo_apilar_en_una_pila_vacia_y_el_tope_es_el_elemento();
	apilar_varios_elementos_actualiza_correctamente_el_tope();
	puedo_apilar_un_elemento_null();

	pa2m_nuevo_grupo("Pruebas de desapilar");
	no_puedo_desapilar_de_una_pila_null();
	no_puedo_desapilar_de_una_pila_vacia();
	desapilar_de_una_pila_devuelve_el_elemento_y_actualiza_el_tope();
	desapilar_varios_elementos_actualiza_el_tope_correctamente();
	desapilar_todos_los_elementos_deja_la_pila_vacia();
	desapilar_devuelve_los_elementos_en_el_orden_correcto();

	pa2m_nuevo_grupo("Pruebas de ver tope");
	el_tope_de_una_pila_null_es_null();
	el_tope_de_una_pila_vacia_es_null();
	apilar_y_desapilar_varios_elementos_actualiza_correctamente_el_tope();

	return pa2m_mostrar_reporte();
}
