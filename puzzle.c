#include "preprocess.h"
#include "defines.h"
#include "puzzle.h"
#include <stdio.h>

puzzle *make_puzzle(char *arreglo) {
  puzzle *p = (puzzle*) malloc(sizeof(puzzle));
  memcpy(p->tablero,arreglo,NxNxchar);
  p->costo     = 0;
  p->profu     = 0;
  p->pos_vacia = 0;
  p->cerrado   = 0;
  return p;
}

puzzle *make_str_puzzle(const char *tablero) {
  puzzle *p = malloc(sizeof(puzzle));

  char num[2];
  int k,i,final=strlen(tablero);
  for(i=0,k=0;i<final;k++){
    if(tablero[i+1]==','||i==final) {
      num[0]='0';
      num[1]=tablero[i];
      i+=2;
    } else {
      num[0]=tablero[i];
      num[1]=tablero[i+1];
      i+=3;
    }
    p->tablero[k] = atoi(num);
    if (!p->tablero[k])
      p->pos_vacia = k;
  }
  p->cerrado   = 0;
  return p;
}

puzzle_list *sucesores(const puzzle *p) {
  puzzle_list *tmp,*l = NULL;
  puzzle *ptmp;

  int fila_vacia = get_fila(p->pos_vacia);
  int col_vacia  = get_col (p->pos_vacia);

  // para arriba:
  if (fila_vacia && p->anterior != ABAJO) {
    puzzle_list *tmp = malloc(sizeof(puzzle_list));
    tmp->p = malloc(sizeof(puzzle));
    memcpy(tmp->p->tablero,p->tablero,NxNxchar);
    tmp->p->tablero[p->pos_vacia]   = p->tablero[p->pos_vacia-N];
    tmp->p->tablero[p->pos_vacia-N] = 0;
    tmp->p->pos_vacia = p->pos_vacia-N;
    tmp->p->anterior  = ARRIBA;
    tmp->p->cerrado = 0;
    SGLIB_LIST_ADD(puzzle_list,l,tmp,next)
  }
  // para derecha:
  if (col_vacia < N_1 && p->anterior != IZQUIERDA) {
    puzzle_list *tmp = malloc(sizeof(puzzle_list));
    tmp->p = malloc(sizeof(puzzle));
    memcpy(tmp->p->tablero,p->tablero,NxNxchar);
    tmp->p->tablero[p->pos_vacia]   = p->tablero[p->pos_vacia+1];
    tmp->p->tablero[p->pos_vacia+1] = 0;
    tmp->p->pos_vacia = p->pos_vacia+1;
    tmp->p->anterior  = DERECHA;
    tmp->p->cerrado = 0;
    //    printf("\tderecha posvacia %d\n",tmp->p.pos_vacia);
    SGLIB_LIST_ADD(puzzle_list,l,tmp,next)
  }
  // para abajo
  if (fila_vacia < N_1 && p->anterior != ARRIBA) {
    puzzle_list *tmp = malloc(sizeof(puzzle_list));
    tmp->p = malloc(sizeof(puzzle));
    memcpy(tmp->p->tablero,p->tablero,NxNxchar);
    tmp->p->tablero[p->pos_vacia]   = p->tablero[p->pos_vacia+N];
    tmp->p->tablero[p->pos_vacia+N] = 0;
    tmp->p->pos_vacia = p->pos_vacia+N;
    tmp->p->anterior  = ABAJO;
    tmp->p->cerrado = 0;
    //    printf("\tabajo posvacia %d\n",tmp->p.pos_vacia);
    SGLIB_LIST_ADD(puzzle_list,l,tmp,next)
  }
  // para izquierda:
  if (col_vacia && p->anterior != DERECHA) {
    puzzle_list *tmp = malloc(sizeof(puzzle_list));
    tmp->p = malloc(sizeof(puzzle));
    memcpy(tmp->p->tablero,p->tablero,NxNxchar);
    tmp->p->tablero[p->pos_vacia]   = p->tablero[p->pos_vacia-1];
    tmp->p->tablero[p->pos_vacia-1] = 0;
    tmp->p->pos_vacia = p->pos_vacia-1;
    tmp->p->anterior  = IZQUIERDA;
    tmp->p->cerrado = 0;
    //    printf("\tizqu posvacia %d\n",tmp->p.pos_vacia);
    SGLIB_LIST_ADD(puzzle_list,l,tmp,next)
  }
  return l;
}

void mutar_arriba(puzzle *p) {
  p->tablero[p->pos_vacia]   = p->tablero[p->pos_vacia-N];
  p->tablero[p->pos_vacia-N] = 0;
  p->pos_vacia = p->pos_vacia-N;
  //p->anterior  = ARRIBA; 
}

void mutar_derecha(puzzle *p) {
  p->tablero[p->pos_vacia]   = p->tablero[p->pos_vacia+1];
  p->tablero[p->pos_vacia+1] = 0;
  p->pos_vacia = p->pos_vacia+1;
  //p->anterior  = DERECHA;
}

void mutar_abajo(puzzle *p) {
  p->tablero[p->pos_vacia]   = p->tablero[p->pos_vacia+N];
  p->tablero[p->pos_vacia+N] = 0;
  p->pos_vacia = p->pos_vacia+N;
  //p->anterior  = ABAJO;  
}

void mutar_izquierda(puzzle *p) {
  p->tablero[p->pos_vacia]   = p->tablero[p->pos_vacia-1];
  p->tablero[p->pos_vacia-1] = 0;
  p->pos_vacia = p->pos_vacia-1;
  //>anterior  = IZQUIERDA;
}

#ifdef CERO
int heuristica(const puzzle *p) {
  return 0;
}
#else
int heuristica(const puzzle *p) {
  int sum,i;
  
  for(i = 0,sum=0; i!=NxN; i++)
    sum += MANHATTAN[p->tablero[i]][i];
  return sum;
}
#endif

inline int objetivo(const puzzle *p){
   char i; 
  
   for(i=0; i!=NxN && p->tablero[i]==i; i++); 

   return i==NxN;
}

void imprimir(const puzzle *p) {
  int i;
  for(i=0; i!=NxN; i++)
    printf("%d ",p->tablero[i]);
  printf("\b: %d\n",p->costo);
}

