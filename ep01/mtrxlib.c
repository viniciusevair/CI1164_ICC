#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "mtrxlib.h"

struct tMatrix* createMatrix(int size) {
    int i;
    struct tMatrix* m;

    if(! (m = malloc(sizeof(struct tMatrix)))) {
        fprintf(stderr, "Erro ao alocar memória");
        return NULL;
    }

    m->size = size;
    if(! (m->data = calloc(m->size, sizeof(double*)))) {
        fprintf(stderr, "Erro ao alocar memória");
        return NULL;
    }

    for (i = 0; i < m->size; i++)
        if(! (m->data[i] = calloc(m->size, sizeof(double)))) {
            fprintf(stderr, "Erro ao alocar memória");
            return NULL;
        }

    return m;
}

struct tTridMatrix* createTridMatrix(int size) {
    struct tTridMatrix* m;

    if(! (m = malloc(sizeof(struct tTridMatrix)))) {
        fprintf(stderr, "Erro ao alocar memória");
        return NULL;
    }

    m->size = size;
    if(! (m->d = calloc(m->size, sizeof(double)))) {
        fprintf(stderr, "Erro ao alocar memória");
        return NULL;
    }
    if(! (m->a = calloc(m->size - 1, sizeof(double)))) {
        fprintf(stderr, "Erro ao alocar memória");
        return NULL;
    }
    if(! (m->c = calloc(m->size - 1, sizeof(double)))) {
        fprintf(stderr, "Erro ao alocar memória");
        return NULL;
    }
    if(! (m->b = calloc(m->size, sizeof(double)))) {
        fprintf(stderr, "Erro ao alocar memória");
        return NULL;
    }

    return m;
}

double* createArray(int size) {
    double* arr;
    if(! (arr = calloc(size, sizeof(double)))) {
        fprintf(stderr, "Erro ao alocar memória");
        return NULL;
    }

    return arr;
}

void deleteArray(double *arr) {
    free(arr);
    arr = NULL;
}

void deleteMatrix(struct tMatrix* m) {
    int i;

    for(i = 0; i < m->size; i++) {
        free(m->data[i]);
        m->data[i] = NULL;
    }
    free(m->data);
    m->data = NULL;
    free(m);
    m = NULL;
}

void readInput(struct tMatrix *matrix, double *b) {
    int i, j;

    for(i = 0; i < matrix->size; i++) {
        for(j = 0; j < matrix->size; j++)
            scanf("%lf", &matrix->data[i][j]);
        scanf("%lf", &b[i]);
    }
}

void readInputTrid(struct tTridMatrix *matrixTrid) {
    int i, j;
    struct tMatrix *aux = createMatrix(matrixTrid->size);
    readInput(aux, matrixTrid->b);
    for (i = 0; i < matrixTrid->size; i++) {
        matrixTrid->d[i] = aux->data[i][i];
        if (i < matrixTrid->size - 1)
            matrixTrid->c[i] = aux->data[i][i + 1];
        if (i > 0)
            matrixTrid->a[i - 1] = aux->data[i][i - 1];
    }
}

/*
 * Função para debugging. Imprime o sistema linear na saída padrão.
 */
void printMatrix(struct tMatrix* m, double *b) {
    int i, j;

    for (i = 0; i < m->size; i++) {
        for (j = 0; j < m->size; j++)
            printf("%lf   ", m->data[i][j]);
        printf("%lf\n", b[i]);
    }
}

void printArray(double *x, int size) {
    for(int i = 0; i < size - 1; i++)
        printf("x[%d] = %lf ", i, x[i]);
    printf("x[%d] = %lf\n", size - 1, x[size - 1]);
}

void printSolution(struct tMatrix *m, double *b, struct tMatrix *originalMatrix, double *c) {
    int i, j;
    double solution[m->size];
    double residual[m->size];

    for(i = m->size - 1; i >= 0; i--) {
        solution[i] = b[i];
        for(j = i + 1; j < m->size; j++)
            solution[i] -= m->data[i][j] * solution[j];
        solution[i] /= m->data[i][i];
    }
    for(i = 0; i < m->size; i++) {
        residual[i] = (-1) * c[i];
        for(j = 0; j < m->size; j++)
            residual[i] += originalMatrix->data[i][j] * solution[j];
    }

    printf("X = [");
    for(i = 0; i < m->size - 1; i++)
        printf("%.12f   ", solution[i]);
    printf("%.12f]\n", solution[i]);
    printf("R = [");
    for(i = 0; i < m->size - 1; i++)
        printf("%.8e   ", residual[i]);
    printf("%.8e]\n", residual[i]);
}

void swapLines(struct tMatrix* m, int a, int b) {
    double* auxPointer = m->data[a];
    m->data[a] = m->data[b];
    m->data[b] = auxPointer;
}

int getMaxColumnValue(struct tMatrix* m, int column) {
    int candidate = column;

    for(int j = column + 1; j < m->size; j++)
        if(fabs(m->data[candidate][column]) < m->data[j][column])
            candidate = j;

    return candidate;
}

void pivoting(struct tMatrix* m, int i) {
    int pivotCandidate = getMaxColumnValue(m, i);

    if(pivotCandidate != i)
        swapLines(m, i, pivotCandidate);
}

void gaussianElim(struct tMatrix* m, double *b) {
    for(int i = 0; i < m->size; i++) {
        pivoting(m, i);

        for(int row = i + 1; row < m->size; row++) {
            double multiplier = m->data[row][i] / m->data[i][i];

            m->data[row][i] = 0.0;
            for(int col = i + 1; col < m->size; col++)
                m->data[row][col] -= m->data[i][col] * multiplier;
            b[row] -= b[i] * multiplier;
        }
    }
}

double getMaxDiff(double *a, double *b, int size){
    double currentErr;
    double maxErr = 0.0;
    for(int i = 0; i < size; i++) {
        currentErr = fabs(fabs(a[i]) - fabs(b[i]));
        if(currentErr > maxErr)
            maxErr = currentErr;
    }

    return maxErr;
}

/* Tolerância é 10^-4, iteração máxima 50. */
int gaussSeidel(struct tMatrix *m, double *b, double *x, double tol) {
    double err = 1 + tol;
    double s;
    double *lastIteration = createArray(m->size);
    int i, j;
    int it = 0;

    while (err > tol && it < 50) {
        for(i = 0; i < m->size; i++) {
            s = 0; 
            for (j = 0; j < m->size; j++) {
                if(i != j)
                    s = s + m->data[i][j] * x[j];
            }
            x[i] = (b[i] - s) / m->data[i][i];
        }

        //calcula erro entre x e lastIteration
        if(it > 0)
            err = getMaxDiff(x, lastIteration, m->size);
        //troca x e lastIteration
        memcpy(lastIteration, x, sizeof(double) * m->size);
        it++;
    }
    deleteArray(lastIteration);
    return it;
}

int gaussSeidelTrid(double *d, double *a, double *c, double *b,
                    double *x, unsigned int n, double tol) {
    double err = 1 + tol;
    double s;
    double *lastIteration = createArray(n);
    int i, j;
    int it = 0;
    while (err > tol && it < 50) {
        x[0] = (b[0] - c[0] * x[1]) / d[0];
        
        for (i = 1; i < n - 1; i++)
            x[i] = (b[i] - a[i-1] * x[i - 1] - c[i] * x[i + 1]) / d[i];
        x[n - 1] = (b[n - 1] - a[n - 2] * x[n - 2]) / d[n - 1];
        printArray(x, n);
        //calcula erro entre x e lastIteration
        if(it > 0)
            err = getMaxDiff(x, lastIteration, n);
        //troca x e lastIteration
        printf("Erro: %lf\n", err);
        memcpy(lastIteration, x, sizeof(double) * n);
        it++;
    }
    printf("Iterações: %d\n", it);
    deleteArray(lastIteration);
    return it;
}

