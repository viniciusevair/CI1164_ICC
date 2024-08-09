#include <stdio.h>
#include <stdlib.h>    /* exit, malloc, calloc, etc. */
#include <sys/time.h>
#include <getopt.h>    /* getopt */
#include <likwid.h>

#include "matriz.h"
#include "utils.h"

/**
 * Exibe mensagem de erro indicando forma de uso do programa e termina
 * o programa.
 */

static void usage(char *progname)
{
  fprintf(stderr, "Forma de uso: %s [ <ordem> ] \n", progname);
  exit(1);
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

  LIKWID_MARKER_INIT;
  
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

  LIKWID_MARKER_START("MultMatVet");
  rtime_t tempo;
  tempo = timestamp();
  multMatVet (mRow_1, vet, n, n, res);
  tempo = timestamp() - tempo;
  printf("%f\n", tempo);
  LIKWID_MARKER_STOP("MultMatVet");
  //prnVetor (res, n);

  LIKWID_MARKER_START("MultMatVetUJB");
  tempo = timestamp();
  multMatVetUJB (mRow_1, vet, n, n, resUJB);
  tempo = timestamp() - tempo;
  printf("%f\n", tempo);
  LIKWID_MARKER_STOP("MultMatVetUJB");
  //prnVetor (resUJB, n);

  LIKWID_MARKER_START("MultMatMat");
  tempo = timestamp();
  multMatMat (mRow_1, mRow_2, n, resMat);
  tempo = timestamp() - tempo;
  printf("%f\n", tempo);
  LIKWID_MARKER_STOP("MultMatMat");
  //prnMat (resMat, n, n);

  LIKWID_MARKER_START("MultMatMatUJB");
  tempo = timestamp();
  multMatMatUJB(mRow_1, mRow_2, n, resMatUJB);
  tempo = timestamp() - tempo;
  printf("%f\n", tempo);
  LIKWID_MARKER_STOP("MultMatMatUJB");
  //prnMat (resMatUJB, n, n);

#ifdef _DEBUG_
    prnVetor (res, n);
    prnMat (resMat, n, n);
#endif /* _DEBUG_ */

  liberaVetor ((void*) mRow_1);
  liberaVetor ((void*) mRow_2);
  liberaVetor ((void*) resMat);
  liberaVetor ((void*) vet);
  liberaVetor ((void*) res);

  LIKWID_MARKER_CLOSE;
  return 0;
}

