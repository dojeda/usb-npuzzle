#ifndef _COLA_PUZZLE_H_
#define _COLA_PUZZLE_H_
#include "puzzle.h"

#define RED 1
#define BLACK 0

/*Inicializo el puzzle_rb_tree--------------------------------------------------------------*/
/**
 * Implementa un arbol red-black de puzzles
 */
typedef struct __puzzle_rb_tree {
  puzzle *p;
  char color;
  struct __puzzle_rb_tree *left;
  struct __puzzle_rb_tree *right;
} puzzle_rb_tree;

#define PUZZLE_RB_CMPARATOR(x,y) (x->p->costo - y->p->costo)

SGLIB_DEFINE_RBTREE_PROTOTYPES(puzzle_rb_tree, left, right, color, PUZZLE_RB_CMPARATOR)
/*------------------------------------------------------------------------------------------*/

/*Inicializo el hash -----------------------------------------------------------------------*/
typedef puzzle_rb_tree rb_tree;
#define PUZZLE_HASH_COMPARATOR(e1,e2) (memcmp(e1->p->tablero,e2->p->tablero,NxNxchar))

/**
 * Funcion de hash para un puzzle
 */
inline unsigned int puzzle_list_hash_function(rb_tree *e);

SGLIB_DEFINE_RBTREE_PROTOTYPES(rb_tree, left, right, color, PUZZLE_HASH_COMPARATOR)
SGLIB_DEFINE_HASHED_CONTAINER_PROTOTYPES(rb_tree, HASH_SIZE, puzzle_list_hash_function)
/*------------------------------------------------------------------------------------------*/

typedef struct __cola_puzzle {
  puzzle_rb_tree *ptree;
  rb_tree *phash[HASH_SIZE];
} cola_puzzle;

/**
 * Inserta un puzzle en la cola de puzzles. Si el elemento ya existe
 * lo actualizo con el nuevo costo siempre y cuando el costo de \a p
 * sea menor que el del puzzle existente.
 * \param c cola de puzzle donde voy a insertar \a p
 * \param p puzzle que voy a insertar en la cola \a c
 */
void insert(cola_puzzle *c, puzzle *p);

/**
 * Verifica si la cola \a c contiene el puzzle \a p
 * \param c cola de puzzle donde voy a verificar \a p
 * \param p puzzle que voy a verificar
 */
int contains(cola_puzzle *c, puzzle *p);

/**
 * Verifica si la cola \a c esta vacia
 * \param c cola de puzzle donde voy a verificar \a p
 */
int empty(cola_puzzle *c);

/**
 * Retorna el puzzle con el menor costo en la cola y luego
 * se elimina de la cola
 * \param c cola de donde se sacara el puzzle
 */
inline puzzle *top(cola_puzzle *c);

/**
 * Construye un nuevo cola_puzzle
 * \return un apuntador al nuevo cola puzzle
 */
cola_puzzle *make_cola_puzzle();
#endif
