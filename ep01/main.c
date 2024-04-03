#include <stdio.h>
#include <string.h>
#include "linSys.h"
#include "elimGauss.h"
#include "gaussSeidel.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    int matrixSize;
    double *b, *c;
    rtime_t tempo;
    struct tMatrix *m, *n;
    scanf("%d", &matrixSize);
    m = createMatrix(matrixSize);
    readInput(m);
    n = makeCopy(m);
    //memcpy(n, m, sizeof(struct tMatrix)*m->size*m->size);
    //memcpy(c, b, sizeof(double)*m->size);

    printMatrix(m);
    printf("-----------\n");
    printMatrix(n);

    //tempo = timestamp();
    //gaussianElim(m, b);
    //tempo = timestamp() - tempo;

    //printf("EG clássico:\n");
    //printSolution(m, b, struct tMatrix *originalMatrix, double *c)

    return 0;
}
