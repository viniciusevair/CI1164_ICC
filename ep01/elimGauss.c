#include <math.h>
#include <stdio.h>
#include "linSys.h"

void swapLines(struct tMatrix* m, int a, int b) {
    double* auxPointer = m->data[a];
    m->data[a] = m->data[b];
    m->data[b] = auxPointer;
}

int getMaxColumnValue(struct tMatrix* m, int column) {
    int candidate = column;

    for(int j = column + 1; j < m->size; j++)
        if(fabs(m->data[candidate][column]) < fabs(m->data[j][column]))
            candidate = j;

    return candidate;
}

void pivoting(struct tMatrix* m, int i) {
    int pivotCandidate = getMaxColumnValue(m, i);

    if(pivotCandidate != i)
        swapLines(m, i, pivotCandidate);
}

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

void gaussianElimTrid(double *d, double *a, double *c, double *b,
                      double *x, unsigned int n) {
    for(int i = 0; i < n - 1; i++) {
        double multiplier = a[i] / d[i];

        a[i] = 0.0;
        d[i+1] -= c[i] * multiplier;
        b[i+1] -= b[i] * multiplier;
    }

    x[ n-1 ] = b[ n-1 ] / d[ n-1 ];
    for (int i=n-2; i >= 0; --i)
        x[ i ] = (b[ i ] - c[ i ] * x[ i+1 ]) / d[ i ];
}
