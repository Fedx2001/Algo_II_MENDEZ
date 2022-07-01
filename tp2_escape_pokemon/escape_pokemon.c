#include <ctype.h>
#include "src/sala.h"
#include "src/menu_juego.h"

#define ERROR_EJECUCION -1
#define BUFFER_ENTRADA 1024

char *en_minusculas(char *string)
{
	for(char *p = string; *p != '\0'; p++){
		int caracter = *p;
		*p = (char)tolower(caracter);
	}
	
	return string;
}

void mostrar_mensaje(const char *mensaje)
{
	printf("%s\n", mensaje);
}

void mostrar_reglas()
{
	printf("¿Como juego?\n");
}

void mostrar_m(const char *mensaje, enum tipo_accion accion, void *aux)
{
	printf("%s %d\n", mensaje, accion);
}

bool parsear_entrada(sala_t *sala, char *entrada)
{
	// char *verbo = NULL;
	// char *objeto1 = NULL;
	// char *objeto2 = NULL;

	char entradas[3][20];
	int i = 0;
	char *linea = strtok(entrada, " ");

	while(linea){
		strcpy(entradas[i], linea);
		linea = strtok(NULL, " ");
		i++;
	}

	strcpy(entradas[2], "_");

	int ejecutadas = sala_ejecutar_interaccion(sala, entradas[0], entradas[1], entradas[2], mostrar_m, NULL);
	printf("%i\n", ejecutadas);

	return true;
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
	
	mostrar_reglas();

	menu_t *menu = menu_crear();
	agregar_comando(menu, "ayuda", "Mostrar comandos disponibles");
	agregar_comando(menu, "agarrar <objeto>", "Agarra un objeto conocido");
	agregar_comando(menu, "describir <objeto>", "Describe el objeto pedido");
	agregar_comando(menu, "salir", "Sale del juego");

	char buffer[BUFFER_ENTRADA];

	do{
		printf(">");
		char *entrada = fgets(buffer, BUFFER_ENTRADA, stdin);
		entrada[strlen(entrada)-1] = 0;
		entrada = en_minusculas(entrada);

		parsear_entrada(sala, entrada);

		if(strcmp(entrada, "ayuda") == 0) 
			mostrar_ayuda(menu);
		else if(strcmp(entrada, "describir") == 0) 
			mostrar_mensaje(sala_describir_objeto(sala, "habitacion"));
		else if(strcmp(entrada, "agarrar") == 0) 
			mostrar_mensaje("NO, CHUPALA");
		else if(strcmp(entrada, "salir") == 0) 
			break;

	} while(!sala_escape_exitoso(sala));

	sala_destruir(sala);

	return 0;
}
