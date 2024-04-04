#include <stdio.h>
#include "linSys.h"
#include "elimGauss.h"
#include "gaussSeidel.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    rtime_t tempo;
    int matrixSize;
    scanf("%d", &matrixSize);

    struct tMatrix *m = createMatrix(matrixSize);
    readInput(m);

    //Eliminação Gaussiana clássica
    struct tMatrix *n = makeCopy(m);
    double *x = createArray(matrixSize);
    double *r = createArray(matrixSize);
    tempo = timestamp();
    gaussianElim(n);
    getSolution(n, x);
    tempo = timestamp() - tempo;
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
    tempo = timestamp();
    it = gaussSeidel(m, x, 10e-4);
    tempo = timestamp() - tempo;
    getResidual(x, r, m);

    printf("GS clássico [ %d iterações ]:\n", it);
    printf("%f ms\n", tempo);
    printArray(x, matrixSize);
    printArray(r, matrixSize);
    printf("\n");

    //Eliminação gaussiana tridiagonal
    struct tTridMatrix *o = makeTridCopy(m);
    tempo = timestamp();
    gaussianElimTrid(o->d, o->a, o->c, o->b, x, o->size);
    getTridSolution(o, x);
    tempo = timestamp() - tempo;
    getResidual(x, r, m);

    printf("EG 3-diagonal:\n");
    printf("%f ms\n", tempo);
    printArray(x, matrixSize);
    printArray(r, matrixSize);
    printf("\n");

    return 0;
}
