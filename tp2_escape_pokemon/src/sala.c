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

	struct objeto *objeto = hash_obtener(sala->objetos_conocidos, nombre_objeto);

	if(!objeto || !objeto->es_asible) return ERROR;

	objeto = hash_quitar(sala->objetos_conocidos, nombre_objeto);

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

/*
 * Recibe una interaccion y realiza la accion correspondiente a la interaccion si
 * no fue realizada previamente.
 * 
 * Si la accion de la interaccion es invalida, no hace nada.
 * 
 * Si la interaccion se ejecutó correctamente, incrementa la cantidad de interacciones ejecutadas.
 */
void ejecutar_interaccion(sala_t *sala, struct interaccion *a_ejecutar, int *cantidad_ejecutadas, 
			  void (*mostrar_mensaje)(const char *mensaje,
						  enum tipo_accion accion,
						  void *aux),
			  void *aux)
{
	if(!sala || !a_ejecutar || !cantidad_ejecutadas) return;
	
	enum tipo_accion tipo = a_ejecutar->accion.tipo;
	char *mensaje = a_ejecutar->accion.mensaje;

	char *objeto_principal = a_ejecutar->objeto;
	char *objeto_parametro = a_ejecutar->objeto_parametro;
	char *objeto_accion = a_ejecutar->accion.objeto;

	switch(tipo){
	case MOSTRAR_MENSAJE:
		if(mostrar_mensaje && mensaje){
			mostrar_mensaje(mensaje, tipo, aux);
			(*cantidad_ejecutadas)++;
		}
		break;
	case DESCUBRIR_OBJETO:
		if(hash_contiene(sala->objetos_conocidos, objeto_accion) ||
			hash_contiene(sala->objetos_poseidos, objeto_accion)){
			break;
		} else {
			if(((struct objeto *)hash_obtener(sala->objetos, objeto_principal))->es_asible
				&& !hash_contiene(sala->objetos_poseidos, objeto_principal)){
				break;
			}

			struct objeto *objeto = hash_obtener(sala->objetos, objeto_accion);
			if(!objeto) break;
			
			hash_t *resultado = hash_insertar(sala->objetos_conocidos, objeto->nombre, objeto, NULL);
			if(!resultado) break;

			if(mostrar_mensaje && mensaje) mostrar_mensaje(mensaje, tipo, aux);
			
			(*cantidad_ejecutadas)++;
		}
		break;
	case REEMPLAZAR_OBJETO:
		if(((struct objeto *)hash_obtener(sala->objetos, objeto_principal))->es_asible
			&& !hash_contiene(sala->objetos_poseidos, objeto_principal)){
			break;
		} else {
			struct objeto *nuevo = hash_obtener(sala->objetos, objeto_accion);
			struct objeto *viejo = hash_quitar(sala->objetos_conocidos, objeto_parametro);
			if(!viejo || !nuevo) break;
			
			hash_t *resultado = hash_insertar(sala->objetos_conocidos, nuevo->nombre, nuevo, NULL);
			if(!resultado) break;
			
			if(mostrar_mensaje && mensaje) mostrar_mensaje(mensaje, tipo, aux);
			
			(*cantidad_ejecutadas)++;
		}

		break;
	case ELIMINAR_OBJETO:
		if(((struct objeto *)hash_obtener(sala->objetos, objeto_principal))->es_asible
			&& !hash_contiene(sala->objetos_poseidos, objeto_principal)){
			break;
		} else {
			struct objeto *quitado = hash_quitar(sala->objetos, objeto_principal);
			if(!quitado) break;

			hash_quitar(sala->objetos_conocidos, objeto_principal);
			hash_quitar(sala->objetos_poseidos, objeto_principal);
			
			free(quitado);

			if(mostrar_mensaje && mensaje) mostrar_mensaje(mensaje, tipo, aux);

			(*cantidad_ejecutadas)++;

			break;
		}
	case ESCAPAR:
		if(((struct objeto *)hash_obtener(sala->objetos, objeto_principal))->es_asible
			&& !hash_contiene(sala->objetos_poseidos, objeto_principal)){
			break;
		}

		if(hash_contiene(sala->objetos_conocidos, objeto_principal) ||
			hash_contiene(sala->objetos_poseidos, objeto_principal)){
			sala->escape_exitoso = true;
		
			if(mostrar_mensaje && mensaje) mostrar_mensaje(mensaje, tipo, aux);
			
			(*cantidad_ejecutadas)++;
		}
		break;
	case ACCION_INVALIDA:
		break;
	}
}

/*
 * Recibe dos interacciones no nulas, compara sus objetos y verbos y 
 * devuelve 0 si la interaccion a comparar tiene los mismos objetos y verbos
 * que otra interacción y -1 en caso que no sea asi.
 */
int comparar_interacciones(void *interaccion_comparada, void *interaccion_a_comparar);

int sala_ejecutar_interaccion(sala_t *sala, const char *verbo,
			      const char *objeto1, const char *objeto2,
			      void (*mostrar_mensaje)(const char *mensaje,
						      enum tipo_accion accion,
						      void *aux),
			      void *aux)
{
	int cantidad_ejecutadas = 0;

	if(!sala || !verbo || !objeto1) return cantidad_ejecutadas;

	struct interaccion a_comparar;
	
	strcpy(a_comparar.verbo, verbo);
	strcpy(a_comparar.objeto, objeto1);
	
	if(!objeto2) strcpy(a_comparar.objeto_parametro, "_");
	else strcpy(a_comparar.objeto_parametro, objeto2);

	lista_iterador_t *it = lista_iterador_crear(sala->interacciones);

	for(; lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it)){
		struct interaccion *actual = lista_iterador_elemento_actual(it);

		if(comparar_interacciones(actual, &a_comparar) == COMPARACION_EXITO)
			ejecutar_interaccion(sala, actual, &cantidad_ejecutadas, mostrar_mensaje, aux);
	}

	lista_iterador_destruir(it);

	return cantidad_ejecutadas;
}

int comparar_interacciones(void *interaccion_comparada, void *interaccion_a_comparar)
{
	struct interaccion *actual = interaccion_comparada;
	struct interaccion *a_comparar = interaccion_a_comparar;
	
	int comparacion_verbo = strcmp(actual->verbo, a_comparar->verbo);
	int comparacion_objeto1 = strcmp(actual->objeto, a_comparar->objeto);
	int comparacion_objeto2 = strcmp(actual->objeto_parametro, a_comparar->objeto_parametro);		

	if(comparacion_verbo == COMPARACION_EXITO && 
	   comparacion_objeto1 == COMPARACION_EXITO && 
	   comparacion_objeto2 == COMPARACION_EXITO
	) 
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

	void *encontrada = lista_buscar_elemento(sala->interacciones, comparar_interacciones, &a_comparar);

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
