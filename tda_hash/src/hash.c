#include "hash.h"

struct par_hash{
	char *clave;
	void *valor;
};

struct nodo_hash {
	struct par_hash *par;
	struct nodo_hash *siguiente;
};

struct hash {
	size_t capacidad;
	size_t ocupados;
	void **tabla;
};

/*
* Possible hashing function
*/
static size_t getHash(const char* source)
{    
    if (source == NULL) {
        return 0;
    }

    size_t hash = 0;
    while (*source != '\0') {
        char c = *source++;
        int a = c - '0';
        hash = (hash * 10) + a;     
    } 
    return hash;
}

size_t hashear_clave(char *clave, size_t capacidad)
{
	return 0;
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

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
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
	return 0;
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

