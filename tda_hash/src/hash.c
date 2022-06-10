#include "hash.h"
#include <string.h>

struct nodo_hash {
	char *clave;
	void *valor;
	struct nodo_hash *siguiente;
};

struct hash {
	size_t capacidad;
	size_t ocupados;
	void **tabla;
};

size_t hashear_clave(char *clave)
{
	size_t hash = 0;

	while(*clave != '\0'){
		hash = *clave + 31*hash;
		*clave++;
	}

	return hash;
}

hash_t *hash_crear(size_t capacidad)
{
	hash_t *hash = malloc(sizeof(hash_t));
	if(!hash)
		return NULL;
	
	if(capacidad <= 3) hash->capacidad = 3;
	else hash->capacidad = capacidad;

	hash->ocupados = 0;

	hash->tabla = malloc(hash->capacidad * sizeof(struct nodo_hash *));
	if(!hash->tabla){
		free(hash);
		return NULL;
	}

	return hash;
}

void rehash()
{

}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if(!clave) return NULL;

	struct nodo_hash *nuevo = malloc(sizeof(struct nodo_hash));
	if(!nuevo)
		return NULL;

	nuevo->siguiente = NULL;
	nuevo->clave = clave;
	nuevo->valor = elemento;

	double factor_carga = hash->ocupados / hash->capacidad;
	if(factor_carga <= 0.75){
		hash->capacidad *= 2;
		rehash(hash);
	}

	size_t clave_hasheada = hashear_clave(clave) % hash->capacidad;
	
	if(!hash->tabla[clave_hasheada]){
		hash->tabla[clave_hasheada] = nuevo;
	} else {
		struct nodo_hash *actual = hash->tabla[clave_hasheada];

		while(actual){
			if(strcmp(actual->clave, clave) == 0){
				*anterior = actual->valor;
				actual->valor = elemento;
				return hash;
			}
			actual = actual->siguiente;
		}
		
		nuevo->siguiente = hash->tabla[clave_hasheada];
		hash->tabla[clave_hasheada] = nuevo;
	}
	
	hash->ocupados += 1;
	*anterior = NULL;

	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	return false;
}

size_t hash_cantidad(hash_t *hash)
{
	if(!hash)
		return 0;

	return hash->ocupados;
}

void hash_destruir(hash_t *hash)
{
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	return 0;
}

