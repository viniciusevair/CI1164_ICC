#include <stdio.h>
#include "mtrxlib.h"

int main(int argc, char *argv[]) {
    int matrixSize;
    struct tTridMatrix *m, *n;
    double *b;
    scanf("%d", &matrixSize);
    printf("The size will be %d\n", matrixSize);

    m = createTridMatrix(matrixSize);
    readInputTrid(m);
    /*
     * Fazer várias cópias da matriz e do vetor com a solução para usar cada um
     * dos métodos especificados no exercício.
     */
    double *x = createArray(matrixSize);
    gaussSeidelTrid(m->d, m->a, m->c, m->b, x, matrixSize, 0.0001);
    printArray(x, matrixSize);

    return 0;
}
