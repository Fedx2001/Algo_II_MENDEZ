#include "src/hash.h"
#include "pa2m.h"

void crear_un_hash_con_capacidad_menor_a_3_crea_un_hash_con_capacidad_3()
{
	hash_t *hash = hash_crear(0);

	pa2m_afirmar(hash != NULL, "Puedo crear un hash con una cantidad menor a 3");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El hash creado esta vacio");

	hash_destruir(hash);
}

void crear_un_hash_de_capacidad_crea_el_hash_correctamente();

void no_puedo_insertar_en_un_hash_NULL();
void no_puedo_insertar_una_clave_NULL();
void puedo_insertar_un_elemento_NULL();
void insertar_un_elemento_con_clave_ya_existente_actualiza_el_elemento();
void insertar_una_clave_con_mismo_hash_que_otra_encadena_la_colision();

int main()
{
	pa2m_nuevo_grupo("Pruebas de algo");

	pa2m_nuevo_grupo("PRUEBAS DE CREACION");
	crear_un_hash_con_capacidad_menor_a_3_crea_un_hash_con_capacidad_3();

	return pa2m_mostrar_reporte();
}