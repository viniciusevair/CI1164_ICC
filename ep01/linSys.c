/* Autores: Luiz Henrique Murback Wiedmer GRR20221234, Vinicius Evair da Silva GRR20221251. */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linSys.h"

/* Aloca memoria para um struct tMatrix* e o retorna.
 * No caso de erro na alocacao a funcao retorna NULL
 * e notifica o usuario. */
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

/* Aloca memoria para um struct tTridMatrix* e o retorna.
 * No caso de erro na alocacao a funcao retorna NULL
 * e notifica o usuario. */
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

/* Aloca memoria para um vetor de double de tamanho size e o retorna.
 * No caso de erro na alocacao a funcao retorna NULL e notifica o usuario. */
double* createArray(int size) {
    double* arr;
    if(! (arr = calloc(size, sizeof(double)))) {
        fprintf(stderr, "Erro ao alocar memória");
        return NULL;
    }

    return arr;
}

/* Libera a memoria apontada por *arr e aponta o ponteiro para NULL. */
void deleteArray(double *arr) {
    free(arr);
    arr = NULL;
}

/* Libera a memoria apontada por *m e aponta o ponteiro para NULL. */
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

/* Le uma entrada inserida pelo usuario no formato de matriz
 * e a insere em *matrix. */
void readInput(struct tMatrix *matrix) {
    int i, j;

    for(i = 0; i < matrix->size; i++) {
        for(j = 0; j < matrix->size; j++)
            scanf("%lf", &matrix->data[i][j]);
        scanf("%lf", &matrix->b[i]);
    }
}

/* Cria uma copia da matriz *m e a retorna. */
struct tMatrix* makeCopy(struct tMatrix *m) {
    struct tMatrix *copy = createMatrix(m->size);

    for (int i = 0; i < m->size; i++) {
        memcpy(copy->data[i], m->data[i], sizeof(double) * m->size);
    }

    memcpy(copy->b, m->b, sizeof(double) * m->size);

    return copy;
}

/* Cria uma copia da matriz *m e a retorna. */
struct tTridMatrix* makeTridCopy(struct tMatrix *m) {
    int i, j;
    struct tTridMatrix *matrixTrid = createTridMatrix(m->size);

    for (i = 0; i < matrixTrid->size; i++) {
        matrixTrid->d[i] = m->data[i][i];
        matrixTrid->b[i] = m->b[i];
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

/* Imprime o vetor *x. */
void printArray(double *x, int size) {
    for(int i = 0; i < size - 1; i++)
        printf("%.12lf ", x[i]);
    printf("%.12lf\n", x[size - 1]);
}

/* Calcula o residuo e o insere no vetor *r. */
void getResidual(double *x, double *r, struct tMatrix *originalMatrix) {
    for(int i = 0; i < originalMatrix->size; i++) {
        r[i] = (-1) * originalMatrix->b[i];
        for(int j = 0; j < originalMatrix->size; j++)
            r[i] += originalMatrix->data[i][j] * x[j];
    }
}
