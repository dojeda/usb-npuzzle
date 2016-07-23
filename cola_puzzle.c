#include "cola_puzzle.h"
#include "cola_impl.h"
#include <stdio.h>

inline unsigned int puzzle_list_hash_function(rb_tree *e) {
  int hash;
  int i;
  for(i=0,hash=0; i!=5; i++)
    hash = hash * 10 + e->p->tablero[i];

  //no hace falta sacarle el modulo pues sglib ya lo hace
  return hash;
} 

cola_puzzle *make_cola_puzzle() {
  cola_puzzle *cola = malloc(sizeof(cola_puzzle));
  sglib_hashed_rb_tree_init(cola->phash);
  cola->ptree = NULL;
  return cola;
}

void insert(cola_puzzle *c, puzzle *p) {
  struct sglib_puzzle_rb_tree_iterator it;
  puzzle ptmp;
  rb_tree *auxh,*member;
  auxh = malloc(sizeof(rb_tree));
  auxh->p = p;
  
  puzzle_rb_tree *auxt,auxa;
  auxt = malloc(sizeof(puzzle_rb_tree));
  auxt->p = p;

  //verifico si esta
  if(sglib_hashed_rb_tree_add_if_not_member(c->phash,auxh,&member)){
    sglib_puzzle_rb_tree_add(&c->ptree,auxt);
  }
}

inline int contains(cola_puzzle *c, puzzle *p){
  int is;
  rb_tree auxh;
  auxh.p = p;

  return sglib_hashed_rb_tree_is_member(c->phash,&auxh);
}

int empty(cola_puzzle *c){
  return c->ptree == NULL;
}

puzzle *top(cola_puzzle *c) {
  rb_tree aux, *member;
  struct sglib_puzzle_rb_tree_iterator it;
  puzzle_rb_tree *te;
  
  te=sglib_puzzle_rb_tree_it_init_inorder(&it,c->ptree);

  //lo borro de ambas estructuras ademas de liberar la memoria
  sglib_puzzle_rb_tree_delete(&c->ptree,te);

  //hago un puzzle_list para poder eliminar este elemento del hash
  aux.p = te->p;
  sglib_hashed_rb_tree_delete_if_member(c->phash,&aux,&member);

  return te->p;
}
