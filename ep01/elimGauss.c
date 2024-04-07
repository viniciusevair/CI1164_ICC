/* Autores: Luiz Henrique Murback Wiedmer GRR22221234, Vinicius Evasir da Silva GRR20221251. */ 

#include <math.h>
#include <stdio.h>
#include "linSys.h"

/* Troca as linhas de indice a e b na matriz *m. */
void swapLines(struct tMatrix* m, int a, int b) {
    double* auxPointer = m->data[a];
    m->data[a] = m->data[b];
    m->data[b] = auxPointer;
}

/* Retorna o maior valor da coluna de indice column na matriz *m. */
int getMaxColumnValue(struct tMatrix* m, int column) {
    int candidate = column;

    for(int j = column + 1; j < m->size; j++)
        if(fabs(m->data[candidate][column]) < fabs(m->data[j][column]))
            candidate = j;

    return candidate;
}

/* Realiza o pivoteamento na coluna i da matriz *m. */
void pivoting(struct tMatrix* m, int i) {
    int pivotCandidate = getMaxColumnValue(m, i);

    if(pivotCandidate != i)
        swapLines(m, i, pivotCandidate);
}

/* Realizas as mudancas necessarias na matriz *m utilizando o metodo 
 * da eliminacao de Gauss para que o sistema linear que ela representa
 * possa ser resolvido pela funcao getSolution. */
void gaussianElim(struct tMatrix* m) {
    for(int i = 0; i < m->size; i++) {
        pivoting(m, i);

        for(int row = i + 1; row < m->size; row++) {
            double multiplier = m->data[row][i] / m->data[i][i];

            m->data[row][i] = 0.0;
            for(int col = i + 1; col < m->size; col++) {
                m->data[row][col] -= m->data[i][col] * multiplier;
            }
            m->b[row] -= m->b[i] * multiplier;
        }
    }
}

/* Realizas as mudancas necessarias nos vetores *d, *a, *b e *c
 * utilizando o metodo da eliminacao de Gauss para matrizes tridiagonais
 * para que o sistema linear que os vetores representam possa ser
 * resolvido pela funcao getSolution. */
void gaussianElimTrid(double *d, double *a, double *c, double *b,
                      double *x, unsigned int n) {
    for(int i = 0; i < n - 1; i++) {
        double multiplier = a[i] / d[i];

        a[i] = 0.0;
        d[i+1] -= c[i] * multiplier;
        b[i+1] -= b[i] * multiplier;
    }
    x[n-1] = b[n-1] / d[n-1];
    for (int i=n-2; i >= 0; --i)
        x[i] = (b[i] - c[i] * x[i+1]) / d[i];
}

/* Insere a solucao do sistema linear representado por *m no vetor *x. */
/* A matriz precisa ter sido processada pelo funcao gaussianElim para
 * que o sistema possa ser resolvido corretamente. */
void getSolution(struct tMatrix *m, double *x) {
    for(int i = m->size - 1; i >= 0; i--) {
        x[i] = m->b[i];
        for(int j = i + 1; j < m->size; j++) {
            x[i] -= m->data[i][j] * x[j];
        }
        x[i] /= m->data[i][i];
    }
}

/* Insere a solucao do sistema linear representado por *m no vetor *x. */
/* A matriz precisa ter sido processada pelo funcao gaussianElimTrid para
 * que o sistema possa ser resolvido corretamente. */
void getTridSolution(struct tTridMatrix *m, double *x) {
    x[m->size - 1] = m->b[m->size - 1] / m->d[m->size - 1];

    for(int i = m->size - 2; i >= 0; i--)
        x[i] = (m->b[i] - m->c[i] * x[i + 1]) / m->d[i];
}
