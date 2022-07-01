#include "src/funciones_escape.h"

void mostrar_mensaje(const char *mensaje, enum tipo_accion accion, void *aux)
{
	switch(accion){
	case ESCAPAR:
		printf(AMARILLO "%s\n", mensaje);
		printf("Besitos besitos, chau chau.\n" NORMAL);
		break;
	case ACCION_INVALIDA:
		printf(ROJO "No" AMARILLO " puedo hacer eso\n" NORMAL);
		break;
	default:
		printf(AMARILLO "%s\n" NORMAL, mensaje);
		break;
	}
}

void mostrar_ayuda()
{
	printf(LIMPIAR_PANTALLA);
	printf(ROJO "==================================================================\n");
	printf(AMARILLO "PAGINA DE AYUDA\n");
	printf("Algunos comandos disponibles:\n");
	printf("-ayuda: Muestra esta página\n");
	printf("-describir objeto: Describe el objeto indicado\n");
	printf("-agarrar objeto: Agarra un objeto de la sala (si se puede agarrar)\n");
	printf("-salir: Sale del juego\n" NORMAL);
	printf(ROJO "==================================================================\n");

	printf(NORMAL "Presiona enter para continuar...\n");
	getchar();
	printf(LIMPIAR_PANTALLA);
}

void ejecutar_interaccion_con_palabras(sala_t *sala, char *verbo, char *objeto, char *objeto_parametro)
{
	if(!sala) return;

	if(strcmp(verbo, AYUDA) == 0) {
		mostrar_ayuda();
	} else if(strcmp(verbo, DESCRIBIR) == 0) {
		printf(AMARILLO "%s\n" NORMAL, sala_describir_objeto(sala, objeto));
	} else if(strcmp(verbo, AGARRAR) == 0) {
		if(sala_agarrar_objeto(sala, objeto)){
			printf(AMARILLO "Agarraste el/la %s\n" NORMAL, objeto);
		} else {
			printf(AMARILLO "No puedo agarrar eso\n" NORMAL);
		}
	} else {
		int ejecutadas = sala_ejecutar_interaccion(sala, verbo, objeto, 
								objeto_parametro, 
								mostrar_mensaje, 
								NULL
							  );

		if(ejecutadas == 0) mostrar_mensaje(NULL, ACCION_INVALIDA, NULL);
	}
}

void liberar_vector(char **vector, size_t tamanio)
{
	if(!vector || tamanio == 0) return;

	for(int i = 0; i < tamanio; i++)
		if(vector[i]) free(vector[i]);
}

char *en_minusculas(char *string)
{
	if(!string) return NULL;

	for(char *p = string; *p != '\0'; p++){
		int caracter = *p;
		*p = (char)tolower(caracter);
	}
	
	return string;
}

bool pedir_y_procesar_entrada(sala_t *sala)
{
	char buffer[BUFFER_ENTRADA];
	
	char *entrada = fgets(buffer, BUFFER_ENTRADA, stdin);

	entrada[strlen(entrada)-1] = 0;
	entrada = en_minusculas(entrada);

	char *objetivos[CANTIDAD_OBJETIVOS] = {NULL, NULL, NULL};
	
	int i = 0;
	char *linea = strtok(entrada, " ");
	while(linea){
		objetivos[i] = calloc(1, strlen(linea)+1);
		strcpy(objetivos[i], linea);
		linea = strtok(NULL, " ");
		i++;
	}

	printf(LIMPIAR_PANTALLA);

	if(!objetivos[POSISCION_VERBO] && !objetivos[POSISCION_OBJETO1] && !objetivos[POSISCION_OBJETO2]) {
		printf(ROJO "Ingresa algo por favor ;-;\n" NORMAL);
	} else if(strcmp(objetivos[POSISCION_VERBO], SALIR) == 0 && !objetivos[POSISCION_OBJETO1]) {
		liberar_vector(objetivos, CANTIDAD_OBJETIVOS);
		return true;
	} else {
		ejecutar_interaccion_con_palabras(sala, objetivos[POSISCION_VERBO], 
						  objetivos[POSISCION_OBJETO1], 
						  objetivos[POSISCION_OBJETO2]
						);
	}

	liberar_vector(objetivos, CANTIDAD_OBJETIVOS);

	return false;
}

void mostrar_intro()
{
	printf(LIMPIAR_PANTALLA);
	printf(AMARILLO "Bienvenidx, amante de los pokémon.\n" NORMAL);
	printf("Lamentablemente no estás acá para ser entrenador, así que ¿Qué haces acá? te estarás preguntando. ");
	printf("Hoy te preparamos un reto. Tenés que escaparte de esta habitación.");
	printf("\nPodés interactuar con tu entorno ingresando un verbo y un objeto (o dos si hiciera falta) en la consola.");
	printf("\nPor ejemplo: 'examinar habitacion'.");
	printf("\nO también: 'abrir puerta llave'. (ESTA INTERACCIÓN DEBERÍA ESTAR EN ESTE ORDEN EN EL EJEMPLO >:|)");
	printf("\nTambién contas con los siguientes comandos:\n"
	       "-salir: Sale del juego\n"
	       "-agarrar objeto: Agarra un objeto de la sala (siempre que pueda ser agarrado)\n"
	       "-describir objeto: describe un objeto conocido o en el inventario\n");	
	printf("Ah! Que tonto de mi parte, casi olvidaba un gran detalle. Si en algún momento no te acordás de los comandos" 
	       " disponibles siempre podés consultarlos usando 'ayuda'.\n");
	printf("El juego está diseñado para hacerte pensar, así que ponete creativx con los verbos!\n");
	printf("\nAdelante, tu nueva aventura te espera, y que tengas un buen escape!\n");

	printf(ROJO "\nOOC: No te preocupes de las mayúsculas y minúsculas, de eso me encargo yo detrás de escena ;) (siempre quize usar esa frase de rpl jejejejejeje)\n" NORMAL);

	printf("\nPresiona enter para empezar...\n");
	getchar();
	printf(LIMPIAR_PANTALLA);
}

void mostrar_objetos(sala_t *sala)
{
	int cantidad_conocidos = 0;
	int cantidad_poseidos = 0;

	char **objetos_conocidos = sala_obtener_nombre_objetos_conocidos(sala, &cantidad_conocidos);
	char **objetos_poseidos = sala_obtener_nombre_objetos_poseidos(sala, &cantidad_poseidos);

	printf("\nConoces las siguientes cosas:\n");
	for(int i = 0; i < cantidad_conocidos; i++)
		printf(VERDE "%s\n" NORMAL, objetos_conocidos[i]);

	printf("\nEn tu inventario tenés las siguientes cosas:\n");
	if(cantidad_poseidos == 0)
		printf(ROJO "No tenés nada por ahora.\n" NORMAL);
	
	for(int i = 0; i < cantidad_poseidos; i++)
		printf(VERDE "%s\n" NORMAL, objetos_poseidos[i]);

	free(objetos_conocidos);
	free(objetos_poseidos);
}

int main(int argc, char *argv[])
{
	if(argc != 3)
		return ERROR_EJECUCION;

	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);
	if(!sala) {
		printf("Error al crear la sala de escape\n");
		return ERROR_EJECUCION;
	}
	
	mostrar_intro();

	bool salir = false;

	while(!sala_escape_exitoso(sala) && !salir){
		mostrar_objetos(sala);
		
		printf("\n¿Que querés hacer?");
		printf("\n>");
		
		salir = pedir_y_procesar_entrada(sala);
	}

	if(salir) printf(ROJO "NOOOOOOO VOLVEEEEE ;-; ;-;\n" NORMAL);

	sala_destruir(sala);

	return 0;
}
