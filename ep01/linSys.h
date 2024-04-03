#ifndef __MATRIX_H
#define __MATRIX_H

struct tMatrix {
    double **data;
    double *b;
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

void deleteArray(double *arr);

void deleteMatrix(struct tMatrix* m);

void readInput(struct tMatrix *matrix);

struct tMatrix* makeCopy(struct tMatrix *m);

struct tTridMatrix* makeTridCopy(struct tMatrix *m);

void printMatrix(struct tMatrix* m);

void printArray(double *x, int size);

void printSolution(struct tMatrix *m, struct tMatrix *originalMatrix);


#endif
