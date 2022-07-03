VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2
CC=gcc
EJEMPLO_OBJETOS=ejemplo/objetos.txt
EJEMPLO_INTERS=ejemplo/interacciones.txt
CUSTOM_OBJETOS=custom/objetos.dat
CUSTOM_INTERACCIONES=custom/interacciones.dat

all: clean jugar-ejemplo


pruebas: src/*.c pruebas.c
	$(CC) $(CFLAGS) src/*.c pruebas.c -o pruebas.o

valgrind-pruebas: pruebas
	valgrind $(VFLAGS) ./pruebas.o

compilar-juego: escape_pokemon.c src/*.c
	$(CC) $(CFLAGS) escape_pokemon.c src/*.c -o juego.o

valgrind-ejemplo: compilar-juego
	valgrind $(VFLAGS) ./juego.o $(EJEMPLO_OBJETOS) $(EJEMPLO_INTERS)

jugar-ejemplo: compilar-juego
	./juego.o $(EJEMPLO_OBJETOS) $(EJEMPLO_INTERS)

valgrind-custom: compilar-juego
	valgrind $(VFLAGS) ./juego.o $(CUSTOM_OBJETOS) $(CUSTOM_INTERACCIONES)

jugar-custom: compilar-juego
	./juego.o $(CUSTOM_OBJETOS) $(CUSTOM_INTERACCIONES)

clean:
	rm -f sala pruebas.o juego.o
