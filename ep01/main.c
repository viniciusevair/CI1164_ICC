#include <likwid-marker.h>
#include <stdio.h>
#include <likwid.h>
#include "linSys.h"
#include "elimGauss.h"
#include "gaussSeidel.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    LIKWID_MARKER_INIT;
    rtime_t tempo;
    int matrixSize;
    scanf("%d", &matrixSize);

    struct tMatrix *m = createMatrix(matrixSize);
    readInput(m);

    //Eliminação Gaussiana clássica
    struct tMatrix *n = makeCopy(m);
    double *x = createArray(matrixSize);
    double *r = createArray(matrixSize);
    LIKWID_MARKER_START("eg_classico");
    tempo = timestamp();
    gaussianElim(n);
    getSolution(n, x);
    tempo = timestamp() - tempo;
    LIKWID_MARKER_STOP("eg_classico");
    getResidual(x, r, m);

    printf("EG clássico:\n");
    printf("%f ms\n", tempo);
    printArray(x, matrixSize);
    printArray(r, matrixSize);
    printf("\n");

    deleteArray(x);
    x = NULL;
    deleteArray(r);
    r = NULL;

    //Método iterativo de Gauss-Seidel clássico
    int it;
    x = createArray(matrixSize);
    r = createArray(matrixSize);
    LIKWID_MARKER_START("gs_classico");
    tempo = timestamp();
    it = gaussSeidel(m, x, 10e-4);
    tempo = timestamp() - tempo;
    LIKWID_MARKER_STOP("gs_classico");
    getResidual(x, r, m);

    printf("GS clássico [ %d iterações ]:\n", it);
    printf("%f ms\n", tempo);
    printArray(x, matrixSize);
    printArray(r, matrixSize);
    printf("\n");

    deleteArray(x);
    x = NULL;
    deleteArray(r);
    r = NULL;

    //Eliminação gaussiana tridiagonal
    struct tTridMatrix *o = makeTridCopy(m);
    x = createArray(matrixSize);
    r = createArray(matrixSize);
    LIKWID_MARKER_START("eg_trid");
    tempo = timestamp();
    gaussianElimTrid(o->d, o->a, o->c, o->b, x, o->size);
    getTridSolution(o, x);
    tempo = timestamp() - tempo;
    LIKWID_MARKER_STOP("eg_trid");
    getResidual(x, r, m);

    printf("EG 3-diagonal:\n");
    printf("%f ms\n", tempo);
    printArray(x, matrixSize);
    printArray(r, matrixSize);
    printf("\n");

    deleteArray(x);
    x = NULL;
    deleteArray(r);
    r = NULL;

    //Método iterativo de Gauss-Seidel tridiagonal 
    struct tTridMatrix *p = makeTridCopy(m);
    x = createArray(matrixSize);
    r = createArray(matrixSize);
    LIKWID_MARKER_START("gs_trid");
    tempo = timestamp();
    it = gaussSeidelTrid(p->d, p->a, p->c, p->b, x, p->size, 10e-4);
    tempo = timestamp() - tempo;
    LIKWID_MARKER_STOP("gs_trid");
    getResidual(x, r, m);

    printf("GS 3-diagonal [ %d iterações ]:\n", it);
    printf("%f ms\n", tempo);
    printArray(x, matrixSize);
    printArray(r, matrixSize);
    printf("\n");

    LIKWID_MARKER_CLOSE;
    return 0;
}
