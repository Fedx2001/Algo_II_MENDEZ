#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

int main()
{
	pa2m_nuevo_grupo("Pruebas de ABB");
	pa2m_nuevo_grupo("Prueba de creación");
	puedo_crear_un_abb();

	pa2m_nuevo_grupo("Pruebas de Inserción");
	insertar_en_abb_vacio_inserta_en_la_raiz();
	insertar_un_elemento_mayor_que_la_raiz_inserta_en_la_derecha_de_la_raiz();
	insertar_un_elemento_menor_que_la_raiz_inserta_en_la_izquierda_de_la_raiz();


	return pa2m_mostrar_reporte();
}
