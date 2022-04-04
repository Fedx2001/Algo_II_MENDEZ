#include <stdio.h>
#include <stdlib.h>

struct objeto {
	int valor;
};

struct sala {
	struct objeto **objetos;
	int cant_objs;
};

int main()
{
	struct sala *s = malloc(sizeof(struct sala));
	if(!s) {
		return 0;
	}

	struct objeto **bloque = malloc(sizeof(struct objeto *));
	if(!bloque) {
		free(s);
		return 0;
	}

	s->cant_objs = 0;
	struct objeto *o;
	for(int i = 0; i < 4; i++) {
		**bloque = realloc(*bloque, (long unsigned int)(s->cant_objs+1) * sizeof(struct objeto));
		if(!*bloque) {
			free(s);
			return 0;
		}

		o = malloc(sizeof(struct objeto));
		if(!o){
			free(*bloque);
			free(bloque);
			free(s);
			return 0;
		}
		o->valor = i;

		bloque[i] = o;
	}

	return 0;
}