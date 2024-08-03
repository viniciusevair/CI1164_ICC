#include <stdio.h>
#include <stdlib.h>    /* exit, malloc, calloc, etc. */
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <getopt.h>    /* getopt */

#include "matriz.h"

/**
 * Exibe mensagem de erro indicando forma de uso do programa e termina
 * o programa.
 */

static void usage(char *progname)
{
  fprintf(stderr, "Forma de uso: %s [ <ordem> ] \n", progname);
  exit(1);
}

typedef double rtime_t;


// Função 
rtime_t timestamp (void)
{
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
  return ( (rtime_t) tp.tv_sec*1.0e3 + (rtime_t) tp.tv_nsec*1.0e-6 );
}


/**
 * Programa principal
 * Forma de uso: matmult [ -n <ordem> ]
 * -n <ordem>: ordem da matriz quadrada e dos vetores
 *
 */

int main (int argc, char *argv[]) 
{
  int n=DEF_SIZE;
  
  MatRow mRow_1, mRow_2, resMat, resMatUJB;
  Vetor vet, res, resUJB;
  
  /* =============== TRATAMENTO DE LINHA DE COMANDO =============== */

  if (argc < 2)
    usage(argv[0]);

  n = atoi(argv[1]);
  
  /* ================ FIM DO TRATAMENTO DE LINHA DE COMANDO ========= */
 
  srandom(20232);
      
  res = geraVetor (n, 1); // (real_t *) malloc (n*sizeof(real_t));
  resMat = geraMatRow(n, n, 1);
  resUJB = geraVetor (n, 1); // (real_t *) malloc (n*sizeof(real_t));
  resMatUJB = geraMatRow(n, n, 1);
    
  mRow_1 = geraMatRow (n, n, 0);
  mRow_2 = geraMatRow (n, n, 0);

  vet = geraVetor (n, 0);

  if (!res || !resMat || !mRow_1 || !mRow_2 || !vet) {
    fprintf(stderr, "Falha em alocação de memória !!\n");
    liberaVetor ((void*) mRow_1);
    liberaVetor ((void*) mRow_2);
    liberaVetor ((void*) resMat);
    liberaVetor ((void*) vet);
    liberaVetor ((void*) res);
    exit(2);
  }
    
#ifdef _DEBUG_
    prnMat (mRow_1, n, n);
    prnMat (mRow_2, n, n);
    prnVetor (vet, n);
    printf ("=================================\n\n");
#endif /* _DEBUG_ */


  rtime_t tempo;
  tempo = timestamp();
  multMatVet (mRow_1, vet, n, n, res);
  tempo = timestamp() - tempo;
  printf("Tempo de execução mulMatVet: %f\n", tempo);
  prnVetor (res, n);

  tempo = timestamp();
  multMatVetUJB (mRow_1, vet, n, n, resUJB);
  tempo = timestamp() - tempo;
  printf("Tempo de execução mulMatVetUJB: %f\n", tempo);
  prnVetor (resUJB, n);

  tempo = timestamp();
  multMatMatUJB(mRow_1, mRow_2, n, resMatUJB);
  tempo = timestamp() - tempo;
  printf("Tempo de execução mulMatMatUJB: %f\n", tempo);
  prnMat (resMatUJB, n, n);

  tempo = timestamp();
  multMatMat (mRow_1, mRow_2, n, resMat);
  tempo = timestamp() - tempo;
  printf("Tempo de execução mulMatMat: %f\n", tempo);
  prnMat (resMat, n, n);

#ifdef _DEBUG_
    prnVetor (res, n);
    prnMat (resMat, n, n);
#endif /* _DEBUG_ */

  liberaVetor ((void*) mRow_1);
  liberaVetor ((void*) mRow_2);
  liberaVetor ((void*) resMat);
  liberaVetor ((void*) vet);
  liberaVetor ((void*) res);
  return 0;
}
