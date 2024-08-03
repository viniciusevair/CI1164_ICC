/* Autores: Luiz Henrique Murback Wiedmer GRR20221234, Vinicius Evair da Silva GRR20221251. */ 

#ifndef __MATRIX_H
#define __MATRIX_H

/* Representa um sistema linear. */
struct tMatrix {
    double **data; /* Representa a matriz de coeficientes. */
    double *b; /* Representa o vetor de termos independentes. */
    int size; /* Representa o tamanho da matriz. */
};

/* Representa um sistema linear tridiagonal. */
struct tTridMatrix {
    double *d; /* Representa a diagonal principal. */
    double *a; /* Representa a diagonal inferior a diagonal principal. */
    double *c; /* Representa a diagonal superior a diagonal principal. */
    double *b; /* Representa o vetor de termos independentes. */
    int size; /* Representa o tamanho da matriz. */
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

void getResidual(double *x, double *r, struct tMatrix *originalMatrix);

#endif
