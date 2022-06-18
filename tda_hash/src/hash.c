#include "hash.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define FACTOR_CARGA_LIMITE 0.75
#define INCREMENTO_CAPACIDAD 2
#define ERROR 0
#define PARAR_ITERACION false

struct nodo_hash {
	char *clave;
	void *elemento;
	struct nodo_hash *siguiente;
};

struct hash {
	size_t capacidad;
	size_t ocupados;
	struct nodo_hash **tabla;
};

size_t hashear_clave(const char *clave)
{
	size_t hash = 0;
	int i = 0;

	while(clave[i] != '\0'){
		hash += (size_t)(clave[i] * (i+1));
		i++;
	}

	return hash;
}

hash_t *hash_crear(size_t capacidad)
{
	hash_t *hash = calloc(1, sizeof(hash_t));
	if(!hash)
		return NULL;

	if(capacidad <= 3) hash->capacidad = 3;
	else hash->capacidad = capacidad;

	hash->tabla = calloc(1, hash->capacidad * sizeof(struct nodo_hash *));
	if(!hash->tabla){
		free(hash);
		return NULL;
	}

	return hash;
}

struct nodo_hash **rehash(struct nodo_hash **tabla_vieja, size_t tamanio)
{
	if(!tabla_vieja) return NULL;

	if(tamanio < 3) return NULL;

	size_t nuevo_tamanio = tamanio * INCREMENTO_CAPACIDAD;

	struct nodo_hash **nueva_tabla = calloc(1, (nuevo_tamanio) * sizeof(struct nodo_hash *));
	if(!nueva_tabla) return NULL;

	for(int i = 0; i < tamanio; i++){
		struct nodo_hash *actual = tabla_vieja[i];

		while(actual){
			size_t clave_hasheada = hashear_clave(actual->clave) % (nuevo_tamanio);

			struct nodo_hash *aux = actual->siguiente;

			actual->siguiente = nueva_tabla[clave_hasheada];
			nueva_tabla[clave_hasheada] = actual;

			actual = aux;
		}
	}

	return nueva_tabla;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if(!clave) return NULL;

	if(!hash) return NULL;

	double factor_carga = (double)((hash->ocupados+1) / hash->capacidad);
	if(factor_carga >= FACTOR_CARGA_LIMITE){
		struct nodo_hash **nueva_tabla = rehash(hash->tabla, hash->capacidad);
		if(!nueva_tabla) return NULL;

		hash->capacidad *= INCREMENTO_CAPACIDAD;

		free(hash->tabla);

		hash->tabla = nueva_tabla;
	}

	struct nodo_hash *nuevo_nodo = calloc(1, sizeof(struct nodo_hash));
	if(!nuevo_nodo) return NULL;

	nuevo_nodo->clave = malloc(strlen(clave)+1);
	if(!nuevo_nodo->clave){
		free(nuevo_nodo);
		return NULL;
	}
	strcpy(nuevo_nodo->clave, clave);

	nuevo_nodo->elemento = elemento;

	size_t clave_hasheada = hashear_clave(clave) % hash->capacidad;

	if(!hash->tabla[clave_hasheada]){
		hash->tabla[clave_hasheada] = nuevo_nodo;
	} else {
		struct nodo_hash *actual = hash->tabla[clave_hasheada];

		while(actual){
			if(strcmp(actual->clave, clave) == 0){
				if(anterior) *anterior = actual->elemento;
				actual->elemento = elemento;

				free(nuevo_nodo->clave);
				free(nuevo_nodo);

				return hash;
			}

			actual = actual->siguiente;
		}

		nuevo_nodo->siguiente = hash->tabla[clave_hasheada];
		hash->tabla[clave_hasheada] = nuevo_nodo;
	}

	hash->ocupados += 1;
	if(anterior) *anterior = NULL;

	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if(!hash) return NULL;

	if(!clave) return NULL;

	size_t clave_hasheada = hashear_clave(clave) % hash->capacidad;

	void *elemento = NULL;

	struct nodo_hash *actual = hash->tabla[clave_hasheada];
	if(!actual) return NULL;

	if(strcmp(actual->clave, clave) == 0){
		hash->tabla[clave_hasheada] = actual->siguiente;
		elemento = actual->elemento;

		hash->ocupados--;

		free(actual->clave);
		free(actual);
	} else {
		struct nodo_hash *anterior = actual;
		actual = actual->siguiente;

		while(actual){
			if(strcmp(actual->clave, clave) == 0){
				anterior->siguiente = actual->siguiente;

				elemento = actual->elemento;
				hash->ocupados--;

				free(actual->clave);
				free(actual);

				break;
			}

			anterior = actual;
			actual = actual->siguiente;
		}
	}

	return elemento;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if(!hash) return NULL;

	if(!clave) return NULL;

	size_t clave_hasheada = hashear_clave(clave) % hash->capacidad;
	void *elemento = NULL;

	struct nodo_hash *actual = hash->tabla[clave_hasheada];

	while(actual){
		if(strcmp(actual->clave, clave) == 0){
			elemento = actual->elemento;
			break;
		}

		actual = actual->siguiente;
	}

	return elemento;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if(!hash) return NULL;

	if(!clave) return NULL;

	size_t clave_hasheada = hashear_clave(clave) % hash->capacidad;

	struct nodo_hash *actual = hash->tabla[clave_hasheada];

	while(actual){
		if(strcmp(actual->clave, clave) == 0) return true;

		actual = actual->siguiente;
	}

	return false;
}

size_t hash_cantidad(hash_t *hash)
{
	if(!hash) return ERROR;

	return hash->ocupados;
}

void hash_destruir(hash_t *hash)
{
	if(!hash) return;

	for(int i = 0; i < hash->capacidad; i++){
		struct nodo_hash *actual = hash->tabla[i];
		while(actual){
			struct nodo_hash *siguiente = actual->siguiente;

			free(actual->clave);
			free(actual);

			actual = siguiente;
		}
	}

	free(hash->tabla);

	free(hash);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if(!hash) return;

	if(!destructor) return;

	for(int i = 0; i < hash->capacidad; i++){
		struct nodo_hash *actual = hash->tabla[i];
		while(actual){
			struct nodo_hash *siguiente = actual->siguiente;

			destructor(actual->elemento);

			free(actual->clave);
			free(actual);

			actual = siguiente;
		}
	}

	free(hash->tabla);

	free(hash);
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	if(!f) return ERROR;

	if(!hash) return ERROR;

	size_t claves_iteradas = 0;

	for(int i = 0; i < hash->capacidad; i++){
		struct nodo_hash *actual = hash->tabla[i];

		while(actual){
			claves_iteradas++;

			if(f(actual->clave, actual->elemento, aux) == PARAR_ITERACION) return claves_iteradas;

			actual = actual->siguiente;
		}
	}

	return claves_iteradas;
}

