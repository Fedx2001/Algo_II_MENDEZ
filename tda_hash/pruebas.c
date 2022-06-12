#include "src/hash.h"
#include "pa2m.h"

void crear_un_hash_con_capacidad_menor_a_3_crea_un_hash_con_capacidad_3()
{
	hash_t *hash = hash_crear(0);

	pa2m_afirmar(hash != NULL, "Puedo crear un hash con una cantidad menor a 3");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El hash creado esta vacio");

	hash_destruir(hash);
}

void crear_un_hash_de_capacidad_mayor_a_3_crea_el_hash_correctamente()
{
	hash_t *hash = hash_crear(7);

	pa2m_afirmar(hash != NULL, "Puedo crear un hash con una cantidad mayor a 3");

	hash_destruir(hash);
}


void no_puedo_insertar_en_un_hash_NULL();
void no_puedo_insertar_una_clave_NULL();
void puedo_insertar_un_elemento_NULL();
void insertar_un_elemento_con_clave_ya_existente_actualiza_el_elemento();
void insertar_una_clave_con_mismo_hash_que_otra_encadena_la_colision();
void insertar_varios_elementos_actualiza_la_cantidad_de_elementos_en_el_hash();


void no_puedo_quitar_en_un_hash_NULL();
void no_puedo_quitar_una_clave_NULL();
void no_puedo_quitar_una_clave_que_no_esta_en_hash();
void puedo_quitar_una_clave_existente_en_el_hash();


void no_puedo_obtener_en_un_hash_NULL();
void no_puedo_obtener_un_elemento_con_clave_NULL();
void no_puedo_obtener_un_elemento_con_clave_no_presente_en_hash();
void no_puedo_usar_hash_contiene_con_hash_NULL();
void un_hash_no_contiene_clave_NULL();
void un_hash_no_contiene_elemento_con_clave_no_presente_en_el_hash();

int main()
{
	pa2m_nuevo_grupo("TDA HASH");

	pa2m_nuevo_grupo("Pruebas de creacion");
	crear_un_hash_con_capacidad_menor_a_3_crea_un_hash_con_capacidad_3();
	crear_un_hash_de_capacidad_mayor_a_3_crea_el_hash_correctamente();

	pa2m_nuevo_grupo("Pruebas de insercion");


	pa2m_nuevo_grupo("Pruebas de eliminacion");


	pa2m_nuevo_grupo("Pruebas de hash_contiene y hash_obtener");


	pa2m_nuevo_grupo("Pruebas con cada clave");


	return pa2m_mostrar_reporte();
}