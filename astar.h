#include <stdio.h>
#include "puzzle.h"
#include "cola_puzzle.h"

#define PUZZLE_LIST_COMPARATOR(e1,e2) (memcmp(e1->p->tablero,e2->p->tablero,NxNxchar))

SGLIB_DEFINE_LIST_PROTOTYPES(puzzle_list, PUZZLE_LIST_COMPARATOR, next)
SGLIB_DEFINE_LIST_FUNCTIONS(puzzle_list, PUZZLE_LIST_COMPARATOR, next)

/**
 * Implementacion del algoritmo A*. Encuentra una solucion hacia el nodo 
 * objetivo a partir del estado inicial \f$s_0\f$
 * \param s0 apuntador al puzzle inicial
 */
puzzle *a_estrella(puzzle *s0);
