#include <stdio.h>
#include <limits.h>
#include "idastar.h"
#include "sglib.h"

#define PUZZLE_LIST_COMPARATOR(e1,e2) (memcmp(e1->p->tablero,e2->p->tablero,NxNxchar))
SGLIB_DEFINE_LIST_PROTOTYPES(puzzle_list, PUZZLE_LIST_COMPARATOR, next)
SGLIB_DEFINE_LIST_FUNCTIONS(puzzle_list, PUZZLE_LIST_COMPARATOR, next)


puzzle s0;
int cota_total = 0;
unsigned int expansiones = 0;
unsigned int visitados  = 0;

unsigned char bida_estrella(unsigned char g, unsigned char cota) {
  int suma = g + heuristica(&s0);
  if (suma > cota) {
    cota_total = suma;
    return 0;
  }

  if (objetivo(&s0)) {
    s0.costo   = g;
    cota_total = g;
    return 1;
  }

  unsigned char min = UCHAR_MAX;
  unsigned char aux = s0.anterior;
  int fila_vacia = get_fila(s0.pos_vacia);
  int col_vacia  = get_col (s0.pos_vacia);
  expansiones ++;
  // abajo
  if (fila_vacia < N_1 && s0.anterior != ARRIBA) {
    visitados ++;
    mutar_abajo(&s0);
    s0.anterior = ABAJO;
    if (bida_estrella(g+1,cota))
      return 1;
    min = min > cota_total ? cota_total: min;
    mutar_arriba(&s0);
    s0.anterior = aux;
  }
  // arriba
  if (fila_vacia && s0.anterior != ABAJO) {
    visitados ++;
    mutar_arriba(&s0);
    s0.anterior = ARRIBA;
    if (bida_estrella(g+1,cota))
      return 1;
    min = min > cota_total ? cota_total: min;
    mutar_abajo(&s0);
    s0.anterior = aux;
  }
  // izquierda
  if (col_vacia && s0.anterior != DERECHA) {
    visitados ++;
    mutar_izquierda(&s0);
    s0.anterior = IZQUIERDA;
    if (bida_estrella(g+1,cota))
      return 1;
    min = min > cota_total ? cota_total: min;
    mutar_derecha(&s0);
    s0.anterior = aux;
  }
  // derecha
  if (col_vacia < N_1 && s0.anterior != IZQUIERDA) {
    visitados ++;
    mutar_derecha(&s0);
    s0.anterior = DERECHA;
    if (bida_estrella(g+1,cota))
      return 1;
    min = min > cota_total ? cota_total: min;
    mutar_izquierda(&s0);
    s0.anterior = aux;
  }

  cota_total = min;
  return 0;
}

int ida_estrella() {
  imprimir(&s0);
  int cota = heuristica(&s0);
  printf("%d",cota);
  while (cota < INT_MAX) {
    if (bida_estrella(0,cota))
      return 1;
    cota = cota_total;
    printf(" %d",cota);
    fflush(stdout);
  }
  return 0;
}


int main(int argc, char **argv) {
  char *spuzzle;
  
  if(argc!=2) {
    fprintf(stderr,"usage: %s <instancia>\n",argv[0]);
    fprintf(stderr,"La instancia debe ser de la forma \"1,2,3,....,15\"\n");    
    exit(1);
  }

  spuzzle = argv[1];

  s0 = *make_str_puzzle(spuzzle);
  ida_estrella();
  
  printf("\n");
  printf("Estado Final ----------------------------------------------\n");
  imprimir(&s0);
  printf("-----------------------------------------------------------\n");
  printf("Expandidos: %u Visitados: %u\n",expansiones,visitados);

  return 0;
}
