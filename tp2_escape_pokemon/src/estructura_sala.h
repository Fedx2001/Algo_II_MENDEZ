#include "sala.h"
#include "hash.h"
#include "lista.h"

struct sala{
	hash_t *objetos_conocidos;
	hash_t *objetos_poseidos;
	hash_t *objetos;
	lista_t *interacciones;
	bool escape_exitoso;
};