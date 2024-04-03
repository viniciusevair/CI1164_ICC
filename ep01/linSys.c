#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linSys.h"

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

    m->b = createArray(m->size);

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

void readInput(struct tMatrix *matrix) {
    int i, j;

    for(i = 0; i < matrix->size; i++) {
        for(j = 0; j < matrix->size; j++)
            scanf("%lf", &matrix->data[i][j]);
        scanf("%lf", &matrix->b[i]);
    }
}

struct tMatrix* makeCopy(struct tMatrix *m) {
    struct tMatrix *copy = createMatrix(m->size);

    for (int i = 0; i < m->size; i++) {
        memcpy(copy->data[i], m->data[i], sizeof(double) * m->size);
    }

    memcpy(copy->b, m->b, sizeof(double) * m->size);

    return copy;
}

struct tTridMatrix* makeTridCopy(struct tMatrix *m) {
    int i, j;
    struct tTridMatrix *matrixTrid = createTridMatrix(m->size);

    for (i = 0; i < matrixTrid->size; i++) {
        matrixTrid->d[i] = m->data[i][i];
        if (i < matrixTrid->size - 1)
            matrixTrid->c[i] = m->data[i][i + 1];
        if (i > 0)
            matrixTrid->a[i - 1] = m->data[i][i - 1];
    }

    return matrixTrid;
}

/*
 * Função para debugging. Imprime o sistema linear na saída padrão.
 */
void printMatrix(struct tMatrix* m) {
    int i, j;

    for (i = 0; i < m->size; i++) {
        for (j = 0; j < m->size; j++)
            printf("%lf   ", m->data[i][j]);
        printf("%lf\n", m->b[i]);
    }
}

void printArray(double *x, int size) {
    for(int i = 0; i < size - 1; i++)
        printf("x[%d] = %lf ", i, x[i]);
    printf("x[%d] = %lf\n", size - 1, x[size - 1]);
}
