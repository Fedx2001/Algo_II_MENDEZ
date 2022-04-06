#ifndef LIBERAR_NOMBRES_H_
#define LIBERAR_NOMBRES_H_

/*
 * Recibe un puntero a un vector de nombres de objetos (reservado en forma dinamica)
 * y la cantidad de nombres que tiene, y libera toda la memoria reservada.
 */
void liberar_nombres(char **nombres, int cant_nombres);

#endif