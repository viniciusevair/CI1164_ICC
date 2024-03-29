#ifndef __MATRIX_H
#define __MATRIX_H

struct tMatrix {
    double **data;
    int size;
};

struct tMatrix* createMatrix(int size);

double* createArray(int size);

void deleteMatrix(struct tMatrix* m);

void readInput(struct tMatrix *matrix, double *b);

void printMatrix(struct tMatrix* m, double *b);

void printArray(double *x, int size);

void printSolution(struct tMatrix *m, double *b, struct tMatrix *originalMatrix, double *c);

void gaussianElim(struct tMatrix* m, double *b);

int gaussSeidel(struct tMatrix *m, double *b, double *x, double tol);

void gaussianElimTrid(struct tMatrix* m);

void gaussSeidelTrid(struct tMatrix* m);

#endif
