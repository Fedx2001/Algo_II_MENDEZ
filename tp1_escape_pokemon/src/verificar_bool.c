#include "verificar_bool.h"
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

int verificar_bool(char *string)
{
	if(strcasecmp(string, "true") == 0) {
		return 1;
	} else if(strcasecmp(string, "false") == 0) {
		return 0;
	}
	
	return -1;
}