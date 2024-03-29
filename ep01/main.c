#include <stdio.h>
#include "mtrxlib.h"

int main(int argc, char *argv[]) {
    int matrixSize;
    struct tMatrix *m, *n;
    double *b;
    scanf("%d", &matrixSize);
    printf("The size will be %d\n", matrixSize);

    m = createMatrix(matrixSize);
    b = createArray(matrixSize);
    readInput(m, b);
    /*
     * Fazer várias cópias da matriz e do vetor com a solução para usar cada um
     * dos métodos especificados no exercício.
     */

    printMatrix(m, b);
    double *x = createArray(matrixSize);
    printf("TÁ ZERADO?\n");
    printArray(x, matrixSize);
    gaussSeidel(m, b, x, 10e-4);
    printf("-----\n");
    printMatrix(m, b);
    printf("Solução???\n");
    printArray(x, matrixSize);

    return 0;
}
