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
	hash_t *hash = hash_crear(4);

	pa2m_afirmar(hash != NULL, "Puedo crear un hash con una cantidad mayor a 3");
	pa2m_afirmar(hash_cantidad(hash) == 0, "El hash creado esta vacio");

	hash_destruir(hash);
}


void no_puedo_insertar_en_un_hash_NULL()
{
	pa2m_afirmar(hash_insertar(NULL, "Clave", "a", NULL) == NULL, "No puedo insertar en un hash NULL");
}

void no_puedo_insertar_una_clave_NULL()
{
	hash_t *hash = hash_crear(4);

	pa2m_afirmar(hash_insertar(hash, NULL, "a", NULL) == NULL, "No puedo insertar una clave NULL");

	hash_destruir(hash);
}

void puedo_insertar_un_elemento_NULL()
{
	hash_t *hash = hash_crear(4);

	pa2m_afirmar(hash_insertar(hash, "11111", NULL, NULL) == hash, "Puedo insertar un elemento NULL");

	hash_destruir(hash);
}

void puedo_insertar_varios_elementos()
{
	hash_t *hash = hash_crear(4);
	hash_t *resultado = NULL;
	char elementos[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
	
	for(int i = 0; i < 9; i++){
		resultado = hash_insertar(hash, "a"+i, elementos+i, NULL);
		if(!resultado) break;
	}

	pa2m_afirmar(resultado != NULL, "Pude insertar 8 elementos");

	hash_destruir(hash);
}

void insertar_un_elemento_con_clave_ya_existente_actualiza_el_elemento()
{
	hash_t *hash = hash_crear(4);
	void *anterior = NULL;
	int elemento = 1;
	int nuevo_elemento = 10;

	hash_insertar(hash, "AAAA0001", &elemento, &anterior);
	hash_insertar(hash, "AAAA0001", &nuevo_elemento, &anterior);

	pa2m_afirmar(hash_obtener(hash, "AAAA0001") == &nuevo_elemento, "Insertar una clave existente actualiza el elemento");
	pa2m_afirmar(anterior == &elemento, "Insertar una clave existente almacena el elemento anteriormente asociado a la clave");

	hash_destruir(hash);
}

void puedo_insertar_una_clave_existente_con_anterior_NULL()
{
	hash_t *hash = hash_crear(4);
	hash_t *resultado = NULL;
	int elemento = 1;
	int nuevo_elemento = 10;

	resultado = hash_insertar(hash, "AAAA0001", &elemento, NULL);
	resultado = hash_insertar(hash, "AAAA0001", &nuevo_elemento, NULL);

	pa2m_afirmar(resultado != NULL, "Puedo insertar una clave existente con anterior NULL");

	hash_destruir(hash);
}

void insertar_una_clave_con_mismo_hash_que_otra_no_reemplaza_la_clave_existente()
{
	hash_t *hash = hash_crear(4);
	int elementos[2] = {1, 10};

	hash_insertar(hash, "AAAA0001", elementos, NULL);
	hash_insertar(hash, "AAAA0010", elementos+1, NULL);

	pa2m_afirmar(hash_obtener(hash, "AAAA0001") == elementos && hash_obtener(hash, "AAAA0010") == elementos+1, 
				  "Insertar dos claves con el mismo valor de hash no reemplaza la clave ya existente");

	hash_destruir(hash);
}

void insertar_varios_elementos_actualiza_la_cantidad_de_elementos_en_el_hash()
{
	hash_t *hash = hash_crear(4);
	hash_t *resultado = NULL;
	char elementos[9] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
	char *claves[9] = {"AAAA", "AAAB", "AAAC", "AAAD", "AAAE", "AAAF", "AAAG", "AAAH", "AAAI"};

	for(int i = 0; i < 9; i++){
		resultado = hash_insertar(hash, claves[i], elementos+i, NULL);
		if(!resultado) break;
	}

	pa2m_afirmar(resultado != NULL, "Inserto varios elementos en el hash");
	pa2m_afirmar(hash_cantidad(hash) == 9, "La cantidad de elementos se actualiza correctamente");

	hash_destruir(hash);
}


void no_puedo_quitar_en_un_hash_NULL()
{
	pa2m_afirmar(hash_quitar(NULL, "AAAA") == NULL, "No puedo quitar de un hash NULL");
}

void no_puedo_quitar_una_clave_NULL()
{
	hash_t *hash = hash_crear(4);

	pa2m_afirmar(hash_quitar(hash, NULL) == NULL, "No puedo quitar una clave NULL");

	hash_destruir(hash);
}

void no_puedo_quitar_una_clave_que_no_esta_en_hash()
{
	hash_t *hash = hash_crear(4);

	pa2m_afirmar(hash_quitar(hash, "AAAA") == NULL, "No puedo quitar una clave que no esta en el hash");

	hash_destruir(hash);
}

void puedo_quitar_una_clave_existente_en_el_hash()
{
	hash_t *hash = hash_crear(4);
	char *elemento = "Duke Nukem";

	hash_insertar(hash, "AAAA", elemento, NULL);

	char *quitado = hash_quitar(hash, "AAAA");

	pa2m_afirmar(quitado != NULL, "Puedo quitar una clave que esta en el hash");
	pa2m_afirmar(quitado == elemento, "El elemento quitado es el correcto");

	hash_destruir(hash);
}

void quitar_una_clave_actualiza_la_cantidad_de_elementos()
{
	hash_t *hash = hash_crear(4);
	char *elementos[4] = {"Nadie:", "Absolutamente nadie:", 
			      "Alumnos de Algo2 haciendo los tps:", "https://youtu.be/YWaq5Opv6Wg"};
	char clave[11] = "AAAAAAAAAA";
	char letra = 65;

	for(int i = 0; i < 4; i++){
		clave[10] = letra;
		hash_insertar(hash, clave, elementos+i, NULL);
		letra++;
	}

	hash_quitar(hash, "AAAAAAAAAA");

	pa2m_afirmar(hash_cantidad(hash) == 3, "Quitar una clave del hash actualiza la cantidad de elementos");

	hash_destruir(hash);
}


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
	no_puedo_insertar_en_un_hash_NULL();
	no_puedo_insertar_una_clave_NULL();
	puedo_insertar_un_elemento_NULL();
	puedo_insertar_varios_elementos();
	insertar_un_elemento_con_clave_ya_existente_actualiza_el_elemento();
	puedo_insertar_una_clave_existente_con_anterior_NULL();
	insertar_una_clave_con_mismo_hash_que_otra_no_reemplaza_la_clave_existente();
	insertar_varios_elementos_actualiza_la_cantidad_de_elementos_en_el_hash();


	pa2m_nuevo_grupo("Pruebas de eliminacion");
	no_puedo_quitar_en_un_hash_NULL();
	no_puedo_quitar_una_clave_NULL();
	no_puedo_quitar_una_clave_que_no_esta_en_hash();
	puedo_quitar_una_clave_existente_en_el_hash();
	quitar_una_clave_actualiza_la_cantidad_de_elementos();


	pa2m_nuevo_grupo("Pruebas de hash_contiene y hash_obtener");


	pa2m_nuevo_grupo("Pruebas con cada clave");


	return pa2m_mostrar_reporte();
}