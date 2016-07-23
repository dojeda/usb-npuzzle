#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include <string.h>
#include <stdlib.h>
#include "sglib.h"
#include "defines.h"

#define TRUE 1
#define FALSE 0


#ifdef NO_DIVISION
#define get_fila(i) FILAS[i]
#define get_col(i)  COLUMNAS[i]
#else
#define get_fila(i) (i/N)
#define get_col(i)  (i%N)
#endif


/**Las jugadas posibles*/
#define ARRIBA    1
#define ABAJO     2
#define DERECHA   3
#define IZQUIERDA 4

/**intercambia dos elementos de un arreglo*/
#define intercambiar(tmp,i,c) do { int aux=tmp[i];tmp[i]=tmp[c];tmp[c]=aux; } while (0);

/**
 * Estructura que representa un puzzle de tamaño NxN
 */
typedef struct __puzzle {
  char tablero[NxN];
  unsigned short pos_vacia;
  unsigned short profu;
  unsigned short costo;
  unsigned char  anterior;
  unsigned char  cerrado:1;
} puzzle;

/**
 * Contenedor tipo lista que contiene puzzles
 */
typedef struct __puzzle_list {
  puzzle *p;
  struct __puzzle_list *next;
} puzzle_list;

/**
 * Construye un nuevo puzzle a partir de un arreglo que represente
 * el tablero
 */
puzzle *make_puzzle(char* arreglo);

/**
 * Crea un nuevo puzzle a partir de un string que representa el 
 * tablero
 */
puzzle *make_str_puzzle(const char *tab);

/**
 * Genera la lista de sucesores del \a puzzle \a p
 * \param p apuntador a puzzle
 * \return la lista de sucesores de \a p
 */
puzzle_list *sucesores(const puzzle *p);


void mutar_arriba(puzzle *p);
void mutar_derecha(puzzle *p);
void mutar_abajo(puzzle *p);
void mutar_izquierda(puzzle *p);

/**
 * Evalua la heuristica de un puzzle p. Las heuristicas pueden ser:
 * \li \b Manhattan: \f$h(s)=|x_2-x_1|+|y_2-y_1|\f$
 * \li \b Cero: \f$h(s)=0\f$
 * \param p apuntador a puzzle
 * \return el valor de la heuristica
 */
int heuristica(const puzzle *p);

/**
 * Verifica si el puzzle \a p es objetivo
 * \param p apuntador a puzzle
 * \return si el \a p es objetivo
 */
int objetivo(const puzzle *p);

/**
 * Imprime el tablero de un puzzle
 */
void imprimir(const puzzle *p);
#endif
