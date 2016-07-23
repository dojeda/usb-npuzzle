#include "astar.h"
#include "cola_puzzle.h"

int expandidos = 0;
int visitados  = 0;

puzzle *a_estrella(puzzle *s0) {
  int i = 0;
  cola_puzzle *Q = make_cola_puzzle();

  rb_tree *q_close[HASH_SIZE];
  sglib_hashed_rb_tree_init(q_close);

  puzzle *s;
  puzzle_list *suces;
  rb_tree *tmp, auxh,*aux;
  struct sglib_puzzle_list_iterator it;

  s0->profu = 0;
  s0->costo = heuristica(s0);
  insert(Q,s0);
  while(!empty(Q)) {
    s = top(Q);
    if(objetivo(s)) return s;

    expandidos++;

    int fila_vacia = get_fila(s->pos_vacia);
    int col_vacia  = get_col (s->pos_vacia);
    
    //saco los sucesores
    //abajo
    if (fila_vacia < N_1 && s->anterior != ARRIBA) {
      puzzle *hijo = malloc(sizeof(puzzle));
      memcpy(hijo->tablero,s->tablero,NxNxchar);
      hijo->tablero[s->pos_vacia]   = s->tablero[s->pos_vacia+N];
      hijo->tablero[s->pos_vacia+N] = 0;
      hijo->pos_vacia = s->pos_vacia+N;
      hijo->anterior  = ABAJO;

      //verifico que no este en los cerrados
      visitados++;
      auxh.p = hijo;
      if(!(tmp=sglib_hashed_rb_tree_find_member(q_close,&auxh)) ||
	 !(tmp->p->costo < auxh.p->costo)) {

	if(tmp!=NULL && tmp->p->costo > auxh.p->costo) {
	  sglib_hashed_rb_tree_delete(q_close,tmp);
	}

	hijo->profu = s->profu + 1;
	hijo->costo = hijo->profu + heuristica(hijo);
	if(objetivo(hijo)) return hijo;
	insert(Q,hijo);
      }
    }
    //arriba
    if (fila_vacia && s->anterior != ABAJO) {
      puzzle *hijo = malloc(sizeof(puzzle));
      memcpy(hijo->tablero,s->tablero,NxNxchar);
      hijo->tablero[s->pos_vacia]   = s->tablero[s->pos_vacia-N];
      hijo->tablero[s->pos_vacia-N] = 0;
      hijo->pos_vacia = s->pos_vacia-N;
      hijo->anterior  = ARRIBA;

      //verifico que no este en los cerrados
      visitados++;
      auxh.p = hijo;
      if(!(tmp=sglib_hashed_rb_tree_find_member(q_close,&auxh)) ||
	 !(tmp->p->costo < auxh.p->costo)) {

	if(tmp!=NULL && tmp->p->costo > auxh.p->costo) {
	  sglib_hashed_rb_tree_delete(q_close,tmp);
	}

	hijo->profu = s->profu + 1;
	hijo->costo = hijo->profu + heuristica(hijo);
	if(objetivo(hijo)) return hijo;
	insert(Q,hijo);
      }
    }
    //izquierda
    if (col_vacia && s->anterior != DERECHA) {
      puzzle *hijo = malloc(sizeof(puzzle));
      memcpy(hijo->tablero,s->tablero,NxNxchar);
      hijo->tablero[s->pos_vacia]   = s->tablero[s->pos_vacia-1];
      hijo->tablero[s->pos_vacia-1] = 0;
      hijo->pos_vacia = s->pos_vacia-1;
      hijo->anterior  = IZQUIERDA;

      //verifico que no este en los cerrados
      visitados++;
      auxh.p = hijo;
      if(!(tmp=sglib_hashed_rb_tree_find_member(q_close,&auxh)) ||
	 !(tmp->p->costo < auxh.p->costo)) {

	if(tmp!=NULL && tmp->p->costo > auxh.p->costo) {
	  sglib_hashed_rb_tree_delete(q_close,tmp);
	}

	hijo->profu = s->profu + 1;
	hijo->costo = hijo->profu + heuristica(hijo);
	if(objetivo(hijo)) return hijo;
	insert(Q,hijo);
      }
    }
    //derecha
    if (col_vacia < N_1 && s->anterior != IZQUIERDA) {
      puzzle *hijo = malloc(sizeof(puzzle));
      memcpy(hijo->tablero,s->tablero,NxNxchar);
      hijo->tablero[s->pos_vacia]   = s->tablero[s->pos_vacia+1];
      hijo->tablero[s->pos_vacia+1] = 0;
      hijo->pos_vacia = s->pos_vacia+1;
      hijo->anterior  = DERECHA;

      //verifico que no este en los cerrados
      visitados++;
      auxh.p = hijo;
      if(!(tmp=sglib_hashed_rb_tree_find_member(q_close,&auxh)) ||
	 !(tmp->p->costo < auxh.p->costo)) {

	if(tmp!=NULL && tmp->p->costo > auxh.p->costo) {
	  sglib_hashed_rb_tree_delete(q_close,tmp);
	}

	hijo->profu = s->profu + 1;
	hijo->costo = hijo->profu + heuristica(hijo);
	if(objetivo(hijo)) return hijo;
	insert(Q,hijo);
      }
    }

    //cierro a s
    aux = malloc(sizeof(rb_tree));
    aux->p = s;
    if(!sglib_hashed_rb_tree_add_if_not_member(q_close,aux,&tmp)) {
      free(aux->p);
      free(aux);
    }

    i++;
  }

  printf("AQUI NO DEBERIA LLEGAR!\n");
  
  return NULL; // aqui no deberia llegar
}

int main(int argc, char **argv) {
  puzzle *s0, *sfinal;
  char *spuzzle;
  
  if(argc!=2) {
    fprintf(stderr,"usage: %s <instancia>\n",argv[0]);
    fprintf(stderr,"La instancia debe ser de la forma \"1,2,3,....,15\"\n");    
    exit(1);
  }

  spuzzle = argv[1];
  
  s0 = make_str_puzzle(spuzzle);

  sfinal = a_estrella(s0);
  
  printf("Estado Final ----------------------------------------------\n");
  imprimir(sfinal);
  printf("-----------------------------------------------------------\n");
  printf("exp=%d vis=%d\n",expandidos,visitados);

  return 0;
}
