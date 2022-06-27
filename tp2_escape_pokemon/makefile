VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2
CC = gcc
DEMO_OBJETOS=ejemplo/objetos.txt
DEMO_INTERACCIONES=ejemplo/interacciones.txt
CUSTOM_OBJETOS=custom/objetos.dat
CUSTOM_INTERACCIONES=custom/interacciones.dat

all: clean valgrind-pruebas


pruebas: src/*.c pruebas.c
	$(CC) $(CFLAGS) src/*.c pruebas.c -o pruebas.o

valgrind-pruebas: pruebas
	valgrind $(VFLAGS) ./pruebas.o

juego: escape_pokemon.c src/*.c
	$(CC) $(CFLAGS) escape_pokemon.c src/*.c -o juego.o

valgrind-demo: juego
	valgrind $(VFLAGS) ./juego.o $(DEMO_OBJETOS) $(DEMO_INTERACCIONES)

demo: juego
	./juego.o $(DEMO_OBJETOS) $(DEMO_INTERACCIONES)

valgrind-custom: juego
	valgrind $(VFLAGS) ./juego.o $(CUSTOM_OBJETOS) $(CUSTOM_INTERACCIONES)

custom: juego
	./juego.o $(CUSTOM_OBJETOS) $(CUSTOM_INTERACCIONES)

clean:
	rm -f sala pruebas.o juego.o
