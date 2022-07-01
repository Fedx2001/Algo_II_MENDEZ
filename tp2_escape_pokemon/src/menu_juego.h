#ifndef MENU_JUEGO_H_
#define MENU_JUEGO_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"

typedef struct comando comando_t;

typedef struct menu menu_t;



comando_t *comando_crear(const char *nombre, const char *info);

menu_t *menu_crear();

void agregar_comando(menu_t *menu, const char *nombre, const char *doc);

bool mostrar_comando(const char *nombre, void *comando, void *aux);

void mostrar_ayuda(menu_t *menu);

#endif