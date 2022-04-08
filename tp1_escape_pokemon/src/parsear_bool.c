#include "parsear_bool.h"
#include <stdio.h>
#include <strings.h>

int string_a_bool(char *string)
{
	if(strcasecmp(string, "true") == 0) {
		return 1;
	} else if(strcasecmp(string, "false") == 0) {
		return 0;
	}

	return -1;
}

char *pasear_bool_a_texto(bool flag)
{
	return (flag ? "Válido" : "Inválido");
}