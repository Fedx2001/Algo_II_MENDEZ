#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"
#include "lista.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_LECTURA 1024
#define HASH_TAMANIO_DEFAULT 6
#define INTERACCION_VALIDA true
#define INTERACCION_INVALIDA false
#define COMPARACION_ERROR -1
#define COMPARACION_EXITO 0
#define EXITO true
#define ERROR false

struct sala{
	hash_t *objetos_conocidos;
	hash_t *objetos_poseidos;
	hash_t *objetos;
	lista_t *interacciones;
	bool escape_exitoso;
};

struct aux{
	char **vector;
	int elementos;
};

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	if(!objetos || !interacciones) return NULL;
	
	sala_t *sala = calloc(1, sizeof(sala_t));
	if(!sala) return NULL;
	
	sala->objetos_conocidos = hash_crear(HASH_TAMANIO_DEFAULT);
	sala->objetos_poseidos = hash_crear(HASH_TAMANIO_DEFAULT);
	sala->objetos = hash_crear(HASH_TAMANIO_DEFAULT);
	sala->interacciones = lista_crear();
	sala->escape_exitoso = false;

	if(!sala->objetos_conocidos || !sala->objetos_poseidos || !sala->objetos || !sala->interacciones) 
		return NULL;

	char buffer[MAX_BUFFER_LECTURA];
	char *linea = NULL;

	FILE *f_objetos = fopen(objetos, "r");
	if(!f_objetos){
		sala_destruir(sala);
		return NULL;
	}
	
	int i = 0;
	
	linea = fgets(buffer, MAX_BUFFER_LECTURA, f_objetos);

	while(linea){
		struct objeto *actual = objeto_crear_desde_string(linea);
		hash_t *resultado = hash_insertar(sala->objetos, actual->nombre, actual, NULL);
		if(!actual || !resultado){
			sala_destruir(sala);
			fclose(f_objetos);
			return NULL;
		}
		
		if(i == 0){
			hash_insertar(sala->objetos_conocidos, actual->nombre, actual, NULL);
			i++;
		}
		
		linea = fgets(buffer, MAX_BUFFER_LECTURA, f_objetos);
	}
	fclose(f_objetos);

	FILE *f_interacciones = fopen(interacciones, "r");
	if(!f_interacciones){
		sala_destruir(sala);
		return NULL;
	}

	linea = fgets(buffer, MAX_BUFFER_LECTURA, f_interacciones);
	while(linea){
		struct interaccion *actual = interaccion_crear_desde_string(linea);
		if(!actual || !lista_insertar(sala->interacciones, actual)){
			sala_destruir(sala);
			fclose(f_interacciones);
			return NULL;
		}
		linea = fgets(buffer, MAX_BUFFER_LECTURA, f_interacciones);
	}

	fclose(f_interacciones);

	if(hash_cantidad(sala->objetos) == 0 || lista_vacia(sala->interacciones)){
		sala_destruir(sala);
		return NULL;
	}

	return sala;
}

/*
 * Recibe un nombre de objeto, un objeto y un contenedor con un vector y la cantidad
 * de elementos del mismo, e inserta los nombres de objetos de un hash en el vector
 * del contenedor.
*/
bool agregar_nombres_en_vector(const char *nombre_objeto, void *objeto, void *contenedor)
{
	struct aux *aux = contenedor;

	aux->vector[aux->elementos] = (char *)nombre_objeto;
	aux->elementos += 1;

	return true;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if(!sala) {
		if(cantidad) *cantidad = -1;
		return NULL;
	}

	if(cantidad) *cantidad = (int)hash_cantidad(sala->objetos);

	char **nombres_objs = calloc(1, hash_cantidad(sala->objetos) * sizeof(char *));
	if(!nombres_objs) {
		if(cantidad) *cantidad = -1;
		return NULL;
	}

	struct aux contenedor;
	contenedor.elementos = 0;
	contenedor.vector = nombres_objs;
	
	hash_con_cada_clave(sala->objetos, agregar_nombres_en_vector, &contenedor);

	return nombres_objs;
}

char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
{
	if(!sala){
		if(cantidad) *cantidad = -1;
		return NULL;
	}
	
	if(cantidad) *cantidad = (int)hash_cantidad(sala->objetos_conocidos);

	char **nombres_conocidos = calloc(1, hash_cantidad(sala->objetos_conocidos) * sizeof(char *));
	if(!nombres_conocidos){
		if(cantidad) *cantidad = -1;
		return NULL;
	}

	struct aux contenedor;
	contenedor.elementos = 0;
	contenedor.vector = nombres_conocidos;
	
	hash_con_cada_clave(sala->objetos_conocidos, agregar_nombres_en_vector, &contenedor);
	
	return nombres_conocidos;
}

char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
{
	if(!sala){
		if(cantidad) *cantidad = -1;
		return NULL;
	}
	
	if(cantidad) *cantidad = (int)hash_cantidad(sala->objetos_poseidos);

	char **nombres_poseidos = calloc(1, hash_cantidad(sala->objetos_poseidos) * sizeof(char *));
	if(!nombres_poseidos){
		if(cantidad) *cantidad = -1;
		return NULL;
	}

	struct aux contenedor;
	contenedor.elementos = 0;
	contenedor.vector = nombres_poseidos;
	
	hash_con_cada_clave(sala->objetos_poseidos, agregar_nombres_en_vector, &contenedor);
	
	return nombres_poseidos;
}

bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto)
{
	if(!sala || !nombre_objeto) return ERROR;

	struct objeto *objeto = hash_quitar(sala->objetos_conocidos, nombre_objeto);

	if(!objeto || !objeto->es_asible) return ERROR;

	hash_insertar(sala->objetos_poseidos, objeto->nombre, objeto, NULL);

	return EXITO;
}

char* sala_describir_objeto(sala_t *sala, const char *nombre_objeto)
{
	if(!sala || !nombre_objeto) return NULL;

	struct objeto *objeto = hash_obtener(sala->objetos_conocidos, nombre_objeto);
	if(objeto) return objeto->descripcion;
		
	objeto = hash_obtener(sala->objetos_poseidos, nombre_objeto);
	if(objeto) return objeto->descripcion;

	return NULL;
}

int sala_ejecutar_interaccion(sala_t *sala, const char *verbo,
			      const char *objeto1, const char *objeto2,
			      void (*mostrar_mensaje)(const char *mensaje,
						      enum tipo_accion accion,
						      void *aux),
			      void *aux)
{
	int cantidad_ejecutadas = 0;

	if(!sala || !verbo || !objeto1) return cantidad_ejecutadas;

	lista_iterador_t *it = lista_iterador_crear(sala->interacciones);

	for(; lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it)){
		struct interaccion *interaccion = lista_iterador_elemento_actual(it);

		int cmp_verbo = strcmp(verbo, interaccion->verbo);
		int cmp_objeto1 = strcmp(objeto1, interaccion->objeto);
		int cmp_objeto2 = strcmp(objeto2, interaccion->objeto_parametro);

		if(cmp_verbo == COMPARACION_EXITO && cmp_objeto1 == COMPARACION_EXITO && cmp_objeto2 == COMPARACION_EXITO){
			char *mensaje = interaccion->accion.mensaje;
			enum tipo_accion tipo = interaccion->accion.tipo;

			switch(tipo){
			case DESCUBRIR_OBJETO:
				struct objeto *descubierto = hash_obtener(sala->objetos, interaccion->accion.objeto);

				void *objeto_poseido = hash_contiene(sala->objetos_poseidos, interaccion->accion.objeto);
				void *objeto_conocido = hash_contiene(sala->objetos_conocidos, interaccion->accion.objeto);

				if(descubierto && !objeto_poseido && !objeto_conocido){
					hash_insertar(sala->objetos_conocidos, descubierto->nombre, descubierto, NULL);
					if(mostrar_mensaje && mensaje) mostrar_mensaje(mensaje, tipo, aux);
					cantidad_ejecutadas++;
				}

				break;
			case REEMPLAZAR_OBJETO:
				struct objeto *objeto_nuevo = hash_obtener(sala->objetos, interaccion->accion.objeto);

				if(objeto_nuevo){
					struct objeto *objeto_viejo = hash_quitar(sala->objetos_conocidos, objeto2);
					if(!objeto_viejo) break;
					
					hash_insertar(sala->objetos_conocidos, interaccion->accion.objeto, objeto_nuevo, NULL);
					
					if(mostrar_mensaje && mensaje) mostrar_mensaje(mensaje, tipo, aux);
					
					cantidad_ejecutadas++;
				}

				break;
			case ELIMINAR_OBJETO:
				if(objeto_nuevo){
					struct objeto *a_quitar = hash_quitar(sala->objetos_conocidos, objeto2);
					if(!a_quitar){
						a_quitar = hash_quitar(sala->objetos_poseidos, objeto2);
						if(!a_quitar) break;
					}
					
					if(mostrar_mensaje && mensaje) mostrar_mensaje(mensaje, tipo, aux);

					cantidad_ejecutadas++;
				}

				break;
			}
		}
	}

	if(cantidad_ejecutadas == 0 && mostrar_mensaje) mostrar_mensaje("Nada interesante alcanza tu vista", ACCION_INVALIDA, aux);

	return cantidad_ejecutadas;
}

/*
 * Recibe dos interacciones no nulas, compara sus objetos y verbos y 
 * devuelve 0 si la interaccion a comparar tiene los mismos objetos y verbos
 * que otra interacción y -1 en caso que no sea asi.
 */
int es_interaccion_valida(void *inter_actual, void *inter_a_comparar)
{
	struct interaccion *actual = inter_actual;
	struct interaccion *a_comparar = inter_a_comparar;
	
	int comparacion_verbo = strcmp(actual->verbo, a_comparar->verbo);
	int comparacion_objeto1 = strcmp(actual->objeto, a_comparar->objeto);
	int comparacion_objeto2 = strcmp(actual->objeto_parametro, a_comparar->objeto_parametro);		

	if(comparacion_verbo == 0 && comparacion_objeto1 == 0 && comparacion_objeto2 == 0) 
		return COMPARACION_EXITO;

	return COMPARACION_ERROR;
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,
				const char *objeto2)
{
	if(sala == NULL || verbo == NULL || objeto1 == NULL) return false;

	struct interaccion a_comparar;
	
	strcpy(a_comparar.verbo, verbo);
	strcpy(a_comparar.objeto, objeto1);
	if(!objeto2) strcpy(a_comparar.objeto_parametro, "_");
	else strcpy(a_comparar.objeto_parametro, objeto2);

	void *encontrada = lista_buscar_elemento(sala->interacciones, es_interaccion_valida, &a_comparar);

	return encontrada != NULL ? INTERACCION_VALIDA : INTERACCION_INVALIDA;
}

bool sala_escape_exitoso(sala_t *sala)
{
	if(!sala) return ERROR;

	return sala->escape_exitoso;
}

void sala_destruir(sala_t *sala)
{
	if(sala == NULL) return;

	lista_destruir_todo(sala->interacciones, free);
	hash_destruir_todo(sala->objetos, free);
	hash_destruir(sala->objetos_conocidos);
	hash_destruir(sala->objetos_poseidos);

	free(sala);
}
