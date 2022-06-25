VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2
CC = gcc
DEMO_OBJETOS=ejemplo/objetos.txt
DEMO_INTERACCIONES=ejemplo/interacciones.txt

all: clean valgrind-demo


pruebas: src/*.c pruebas.c
	$(CC) $(CFLAGS) src/*.c pruebas.c -o pruebas.o

valgrind-pruebas: pruebas
	valgrind $(VFLAGS) ./pruebas.o

demo: escape_pokemon.c src/*.c
	$(CC) $(CFLAGS) escape_pokemon.c src/*.c -o demo.o

valgrind-demo: demo
	valgrind $(VFLAGS) ./demo.o $(DEMO_OBJETOS) $(DEMO_INTERACCIONES)

clean:
	rm -f sala pruebas
