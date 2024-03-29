#ifndef __MATRIX_H
#define __MATRIX_H

struct tMatrix {
    double **data;
    int size;
};

struct tTridMatrix {
    double *d;
    double *a;
    double *c;
    double *b;
    int size;
};

struct tMatrix* createMatrix(int size);

struct tTridMatrix* createTridMatrix(int size);

double* createArray(int size);

void deleteMatrix(struct tMatrix* m);

void readInput(struct tMatrix *matrix, double *b);

void readInputTrid(struct tTridMatrix *matrixTrid);

void printMatrix(struct tMatrix* m, double *b);

void printArray(double *x, int size);

void printSolution(struct tMatrix *m, double *b, struct tMatrix *originalMatrix, double *c);

void gaussianElim(struct tMatrix* m, double *b);

int gaussSeidel(struct tMatrix *m, double *b, double *x, double tol);

void gaussianElimTrid(struct tMatrix* m);

int gaussSeidelTrid(double *d, double *a, double *c, double *b,
                    double *x, unsigned int n, double tol);

#endif
