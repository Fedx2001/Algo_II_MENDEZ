#include "pa2mm.h"
#include "src/estructuras.h"
#include "src/sala.h"
#include "src/estructura_sala.h"
#include "src/objeto.h"
#include "src/interaccion.h"

#include "string.h"
#include <stdbool.h>

void pruebasCrearObjeto()
{
	pa2m_afirmar(objeto_crear_desde_string(NULL) == NULL,
		     "No puedo crear un objeto a partir de un string NULL");
	pa2m_afirmar(objeto_crear_desde_string("") == NULL,
		     "No puedo crear un objeto a partir de un string vacío");
	pa2m_afirmar(objeto_crear_desde_string("a;b") == NULL,
		     "\"a;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;;b") == NULL,
		     "\"a;;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string(";a;b") == NULL,
		     "\";a;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;b;c") == NULL,
		     "\"a;b;c\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;;true") == NULL,
		     "\"a;;true\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string(";a;false") == NULL,
		     "\";a;false\" no es un string objeto válido");

	struct objeto *objeto1 = objeto_crear_desde_string("nombre;desc;true");
	pa2m_afirmar(objeto1, "\"nombre;desc;true\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto1->nombre, "nombre") == 0, "El nombre del objeto es \"nombre\"");
	pa2m_afirmar(strcmp(objeto1->descripcion, "desc") == 0,
		     "La descripcion del objeto es \"desc\"");
	pa2m_afirmar(objeto1->es_asible == true, "El objeto es asible");

	struct objeto *objeto2 = objeto_crear_desde_string("A;Be;false\n");
	pa2m_afirmar(objeto2, "\"A;Be;false\\n\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto2->nombre, "A") == 0, "El nombre del objeto es \"A\"");
	pa2m_afirmar(strcmp(objeto2->descripcion, "Be") == 0,
		     "La descripcion del objeto es \"Be\"");
	pa2m_afirmar(objeto2->es_asible == false, "El objeto no es asible");

	free(objeto1);
	free(objeto2);
}

void pruebasCrearInteracciones()
{
	pa2m_afirmar(interaccion_crear_desde_string(NULL) == NULL,
		     "No puedo crear una interacción a partir de un string NULL");
	pa2m_afirmar(interaccion_crear_desde_string("") == NULL,
		     "No puedo crear una interacción a partir de un string vacío");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c:d:e") == NULL,
		     "\"a;b;c:d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c;d") == NULL,
		     "\"a;b;c;d\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c;d:e") == NULL,
		     "\"a;b;c;d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;_;d:e") == NULL,
		     "\"a;b;_;d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;_;de:f:g") == NULL,
		     "\"a;b;_;de:f:g\" no es un string interacción válido");

	struct interaccion *inter1 = interaccion_crear_desde_string("a;b;c;d:e:f");
	pa2m_afirmar(inter1, "\"a;b;c;d:e:f\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter1->objeto, "a") == 0, "El nombre del objeto es \"a\"");
	pa2m_afirmar(strcmp(inter1->verbo, "b") == 0, "El verbo es \"b\"");
	pa2m_afirmar(strcmp(inter1->objeto_parametro, "c") == 0, "El segundo objeto es \"c\"");
	pa2m_afirmar(inter1->accion.tipo == DESCUBRIR_OBJETO,
		     "El tipo de acción es DESCUBRIR_OBJETO");
	pa2m_afirmar(strcmp(inter1->accion.objeto, "e") == 0, "El objeto de la acción es \"e\"");
	pa2m_afirmar(strcmp(inter1->accion.mensaje, "f") == 0, "El mensaje de la acción es \"f\"");

	struct interaccion *inter2 = interaccion_crear_desde_string("OB;VER;_;m:_:MSG");
	pa2m_afirmar(inter1, "\"OB;VER;_;m:_:MSG\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter2->objeto, "OB") == 0, "El nombre del objeto es \"OB\"");
	pa2m_afirmar(strcmp(inter2->verbo, "VER") == 0, "El verbo es \"VER\"");
	pa2m_afirmar(strcmp(inter2->objeto_parametro, "") == 0, "El segundo objeto es vacío");
	pa2m_afirmar(inter2->accion.tipo == MOSTRAR_MENSAJE,
		     "El tipo de acción es MOSTRAR_MENSAJE");
	pa2m_afirmar(strcmp(inter2->accion.objeto, "") == 0, "El objeto de la acción es vacío");
	pa2m_afirmar(strcmp(inter2->accion.mensaje, "MSG") == 0,
		     "El mensaje de la acción es \"MSG\"");

	free(inter1);
	free(inter2);
}

void pruebas_crear_sala()
{
	pa2m_afirmar(sala_crear_desde_archivos("/ASD/ASD/", "dasD/sa2asdd") == NULL,
		     "No puedo crear la sala a partír de archivos inexistentes");

	pa2m_afirmar(sala_crear_desde_archivos("", "chanu/int.csv") == NULL,
		     "No puedo crear la sala sin objetos");

	pa2m_afirmar(sala_crear_desde_archivos("chanu/obj.dat", "chanu/vacio.txt") == NULL,
		     "No puedo crear la sala sin interacciones");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(sala != NULL, "Puedo crear la sala a partir de archivos no vacíos");

	pa2m_afirmar(hash_cantidad(sala->objetos) == 9, "Se leyeron 9 objetos");
	pa2m_afirmar(lista_tamanio(sala->interacciones) == 9, "Se leyeron 9 interacciones");

	sala_destruir(sala);
}

void pruebas_nombre_objetos()
{
	int cantidad = 0;
	pa2m_afirmar(sala_obtener_nombre_objetos(NULL, &cantidad) == NULL,
		     "No puedo obtener los nombres de objetos de una sala NULL");
	pa2m_afirmar(cantidad == -1, "La cantidad es -1 luego de invocar a la función");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	char **objetos = sala_obtener_nombre_objetos(sala, NULL);
	pa2m_afirmar(objetos != NULL,
		     "Puedo pedir el vector de nombres a la sala pasando cantidad NULL");

	char **objetos2 = sala_obtener_nombre_objetos(sala, &cantidad);
	pa2m_afirmar(objetos2 != NULL,
		     "Puedo pedir el vector de nombres a la sala pasando cantidad no NULL");
	pa2m_afirmar(cantidad == 9, "La cantidad de elementos del vector coincide con lo esperado");

	const char *esperados[] = {"habitacion", "mesa", "interruptor", "pokebola", "cajon",
				    "cajon-abierto", "llave", "anillo",	"puerta"};

	int comparaciones_exitosas = 0;

	for (int i = 0; i < cantidad; i++)
		if (strcmp(objetos2[i], esperados[i]) == 0)
			comparaciones_exitosas++;

	pa2m_afirmar(comparaciones_exitosas == cantidad,
		     "Todos los nombres de objeto son los esperados");

	free(objetos);
	free(objetos2);
	sala_destruir(sala);
}

void pruebas_agarrar_objetos()
{
	pa2m_afirmar(!sala_agarrar_objeto(NULL, "pokebola"), "No puedo agarrar un objeto de una sala que no existe");

	sala_t *sala = sala_crear_desde_archivos("test_scene/objetos.txt", "test_scene/interacciones.txt");
	pa2m_afirmar(!sala_agarrar_objeto(sala, NULL), "No puedo agarrar un objeto NULL de una sala");

	pa2m_afirmar(!sala_agarrar_objeto(sala, "mesa"), "No puedo agarrar un objeto que no existe en la sala");

	pa2m_afirmar(!sala_agarrar_objeto(sala, "llave"), "No puedo agarrar un objeto que no conozco");

	pa2m_afirmar(sala_agarrar_objeto(sala, "pokebola"), "Puedo agarrar un objeto que conozco");

	pa2m_afirmar(!sala_agarrar_objeto(sala, "pokebola"), "No puedo volver a agarrar el  mismo objeto");

	sala_destruir(sala);
}

void pruebas_nombre_objetos_conocidos()
{
	int cantidad = 0;
	pa2m_afirmar(sala_obtener_nombre_objetos_conocidos(NULL, &cantidad) == NULL,
		     "No puedo obtener los nombres de objetos conocidos de una sala NULL");
	pa2m_afirmar(cantidad == -1, "La cantidad es -1 luego de invocar a la función");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	char **objetos = sala_obtener_nombre_objetos_conocidos(sala, NULL);
	pa2m_afirmar(objetos != NULL,
		     "Puedo pedir el vector de nombres conocidos a la sala pasando cantidad NULL");

	char **objetos2 = sala_obtener_nombre_objetos_conocidos(sala, &cantidad);
	pa2m_afirmar(objetos2 != NULL,
		     "Puedo pedir el vector de nombres conocidos a la sala pasando cantidad no NULL");
	pa2m_afirmar(cantidad == 1, "La cantidad de elementos del vector coincide con lo esperado");

	const char esperado[] = "habitacion";

	pa2m_afirmar(strcmp(objetos2[cantidad-1], esperado) == 0,
		     "Todos los nombres de objeto son los esperados (SÍ, ME AFANÉ TUS PRUEBAS)");

	free(objetos);
	free(objetos2);
	sala_destruir(sala);
}

void pruebas_nombre_objetos_poseidos()
{
	int cantidad = 0;
	pa2m_afirmar(sala_obtener_nombre_objetos_poseidos(NULL, &cantidad) == NULL,
		     "No puedo obtener los nombres de objetos poseidos de una sala NULL");
	pa2m_afirmar(cantidad == -1, "La cantidad es -1 luego de invocar a la función");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	char **objetos = sala_obtener_nombre_objetos_poseidos(sala, NULL);
	pa2m_afirmar(objetos != NULL,
		     "Puedo pedir el vector de nombres poseidos a la sala pasando cantidad NULL");

	char **objetos2 = sala_obtener_nombre_objetos_poseidos(sala, &cantidad);
	pa2m_afirmar(objetos2 != NULL,
		     "Puedo pedir el vector de nombres poseidos a la sala pasando cantidad no NULL");
	
	pa2m_afirmar(cantidad == 0, "Una sala recién creada no tiene objetos poseidos");

	free(objetos);
	free(objetos2);
	sala_destruir(sala);
}

void pruebas_interacciones()
{
	pa2m_afirmar(sala_es_interaccion_valida(NULL, "hacer", NULL, NULL) == false,
		     "No es válido pedir interacciones de una sala NULL");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(sala_es_interaccion_valida(sala, NULL, "", "") == false, "No es válida una intearcción con verbo NULL");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "hacer", NULL, "") == false, "No es válida una intearcción con objeto NULL");

	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "habitacion", "") == true, "Puedo examinar la habitación");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "usar", "llave", "cajon") == true, "Puedo usar la llave en el cajón");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "pokebola", "") == true, "Puedo abrir la pokebola");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "cajon-abierto", "") == true, "Puedo examinar el cajón abierto");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "romper", "todo", "") == false, "No puedo romper todo");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "mesa", "") == false, "No puedo abrir la mesa");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "techo", "") == false, "No puedo examinar el techo");

	sala_destruir(sala);
}

void pruebas_describir_objeto()
{
	pa2m_afirmar(!sala_describir_objeto(NULL, "pokebola"),
		     "No puedo describir un objeto de una sala NULL");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(!sala_describir_objeto(sala, NULL),
		     "No puedo describir un objeto NULL");

	pa2m_afirmar(!sala_describir_objeto(sala, "pokebola"),
		     "No puedo describir un objeto que no es conocido");

	char *descripcion = sala_describir_objeto(sala, "habitacion");
	pa2m_afirmar(descripcion, "Puedo describir un objeto conocido");

	int comparacion = strcmp(descripcion, "Una habitación de la que no podes escapar");

	pa2m_afirmar(comparacion == 0, "La descripcion es la esperada");

	sala_destruir(sala);
}

struct cantidad_acciones_y_tipo{
	int cantidad_ejecutadas;
	enum tipo_accion accion;
};

void mostrar_mensaje(const char *mensaje, enum tipo_accion accion, void *aux)
{
	struct cantidad_acciones_y_tipo *contenedor = aux;
	if(accion == contenedor->accion) contenedor->cantidad_ejecutadas++;
}

void pruebas_ejecutar_interaccion()
{
	sala_t *sala = sala_crear_desde_archivos("ejemplo/objetos.txt", "ejemplo/interacciones.txt");

	struct cantidad_acciones_y_tipo aux;
	aux.accion = REEMPLAZAR_OBJETO;
	aux.cantidad_ejecutadas = 0;

	int ejecutadas = 0;

	ejecutadas = sala_ejecutar_interaccion(sala, "abrir", "llave", "puerta", mostrar_mensaje, &aux);

	pa2m_afirmar(ejecutadas == 0, "No puedo abrir la puerta si no la conozco");
	pa2m_afirmar(aux.cantidad_ejecutadas == 0, "No se llamo a mostrar mensaje ninguna vez");

	aux.accion = DESCUBRIR_OBJETO;
	ejecutadas = sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", mostrar_mensaje, &aux);

	pa2m_afirmar(ejecutadas == 2, "Examino la habitacion y ejecuto dos interacciones");
	pa2m_afirmar(aux.cantidad_ejecutadas == 2,
		     "Se llamo a mostrar mensaje dos veces con el tipo de accion DESCUBRIR");

	int cantidad = 0;

	char **objetos_conocidos1 = sala_obtener_nombre_objetos_conocidos(sala, &cantidad);
	int comparaciones_exitosas = 0;

	if(strcmp(objetos_conocidos1[0], "pokebola") == 0) comparaciones_exitosas++;
	if(strcmp(objetos_conocidos1[1], "habitacion") == 0) comparaciones_exitosas++;
	if(strcmp(objetos_conocidos1[2], "puerta") == 0) comparaciones_exitosas++;

	pa2m_afirmar(cantidad == 3, "Ahora conozco 3 objetos");
	pa2m_afirmar(comparaciones_exitosas == 3, "Los objetos son pokebola, habitacion y puerta");

	aux.cantidad_ejecutadas = 0;
	ejecutadas = sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", mostrar_mensaje, &aux);

	pa2m_afirmar(ejecutadas == 0, "Examino la habitacion de nuevo y no descubro nada");
	pa2m_afirmar(aux.cantidad_ejecutadas == 0,
		     "No se llamo a mostrar mensaje");

	ejecutadas = sala_ejecutar_interaccion(sala, "abrir", "pokebola", "", NULL, NULL);
	pa2m_afirmar(ejecutadas == 0, "No puedo abrir la pokebola (No la tengo)");

	ejecutadas = sala_ejecutar_interaccion(sala, "abrir", "llave", "puerta", NULL, NULL);
	pa2m_afirmar(ejecutadas == 0, "No puedo abrir la puerta con la llave (No conozco la llave)");

	ejecutadas = sala_ejecutar_interaccion(sala, "salir", "puerta-abierta", "", NULL, NULL);
	pa2m_afirmar(ejecutadas == 0,
		     "No puedo salir por la puerta abierta (PORQUE NO DEBERÍA ESTAR ABIERTA >:|)");

	bool agarrado = sala_agarrar_objeto(sala, "pokebola");
	pa2m_afirmar(agarrado, "Agarré la pokébola");

	ejecutadas = sala_ejecutar_interaccion(sala, "abrir", "pokebola", "", NULL, NULL);
	pa2m_afirmar(ejecutadas == 2, "Abrí la pokébola y se eliminó de la sala");

	ejecutadas = sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", mostrar_mensaje, &aux);
	pa2m_afirmar(ejecutadas == 0, "Examinar la habitación de nuevo no descubre la pokébola (fue eliminada)");

	ejecutadas = sala_ejecutar_interaccion(sala, "abrir", "llave", "puerta", NULL, NULL);
	pa2m_afirmar(ejecutadas == 0, "No puedo abrir la puerta con la llave (No tengo la llave)");

	agarrado = sala_agarrar_objeto(sala, "llave");
	pa2m_afirmar(agarrado, "Agarré la llave");

	ejecutadas = sala_ejecutar_interaccion(sala, "abrir", "llave", "puerta", NULL, NULL);
	pa2m_afirmar(ejecutadas == 1, "Abrí la puerta con la llave");
	pa2m_afirmar(!sala_escape_exitoso(sala), "Todavía no ocurrió un escape exitoso");

	ejecutadas = sala_ejecutar_interaccion(sala, "salir", "puerta-abierta", "", NULL, NULL);
	pa2m_afirmar(ejecutadas == 1, "Me escapé de la sala");
	pa2m_afirmar(sala_escape_exitoso(sala), "Se actualizó el estado del escape a escape exitoso");

	free(objetos_conocidos1);
	sala_destruir(sala);
}

void pruebas_escape_exitoso()
{
	pa2m_afirmar(!sala_escape_exitoso(NULL), "No hay un escape exitoso de una sala NULL");

	sala_t *sala = sala_crear_desde_archivos("test_scene/objs.txt", "test_scene/inters.txt");

	pa2m_afirmar(!sala_escape_exitoso(sala),
		     "No se realizo un escape exitoso de una sala recien creada");

	bool agarrado = sala_agarrar_objeto(sala, "pokebola");
	int ejecutadas = sala_ejecutar_interaccion(sala, "abrir", "pokebola", "", NULL, NULL);

	pa2m_afirmar(agarrado && ejecutadas == 1 && sala_escape_exitoso(sala),
		     "Se realizo un escape exitoso de la sala ejecutando la interaccion adecuada");

	sala_destruir(sala);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de creación de objetos");
	pruebasCrearObjeto();

	pa2m_nuevo_grupo("Pruebas de creación de interacciones");
	pruebasCrearInteracciones();

	pa2m_nuevo_grupo("Pruebas de creación de sala");
	pruebas_crear_sala();

	pa2m_nuevo_grupo("Pruebas del vector de todos los nombres de objetos");
	pruebas_nombre_objetos();

	pa2m_nuevo_grupo("Pruebas de interacciones");
	pruebas_interacciones();

	pa2m_nuevo_grupo("Pruebas de agarrar objetos");
	pruebas_agarrar_objetos();

	pa2m_nuevo_grupo("Pruebas del vector de nombres conocidos");
	pruebas_nombre_objetos_conocidos();

	pa2m_nuevo_grupo("Pruebas del vector de nombres poseidos");
	pruebas_nombre_objetos_poseidos();

	pa2m_nuevo_grupo("Pruebas de describir objetos");
	pruebas_describir_objeto();

	pa2m_nuevo_grupo("Pruebas de ejecutar interaccion (en realidad me afane el ejecutar el escenario de ejemplo de Chanu jejejeje)");
	pruebas_ejecutar_interaccion();

	pa2m_nuevo_grupo("Pruebas de escape exitoso");
	pruebas_escape_exitoso();

	return pa2m_mostrar_reporte();
}
