#include <math.h>
#include <stdio.h>
#include "linSys.h"

void printSolution(struct tMatrix *m, struct tMatrix *originalMatrix) {
    int i, j;
    double solution[m->size];
    double residual[m->size];

    for(i = m->size - 1; i >= 0; i--) {
        solution[i] = m->sol[i];
        for(j = i + 1; j < m->size; j++)
            solution[i] -= m->data[i][j] * solution[j];
        solution[i] /= m->data[i][i];
    }
    for(i = 0; i < m->size; i++) {
        residual[i] = (-1) * originalMatrix->sol[i];
        for(j = 0; j < m->size; j++)
            residual[i] += originalMatrix->data[i][j] * solution[j];
    }

    for(i = 0; i < m->size - 1; i++)
        printf("%.12f   ", solution[i]);
    printf("%.12f\n", solution[i]);
    for(i = 0; i < m->size - 1; i++)
        printf("%.8e   ", residual[i]);
    printf("%.8e\n", residual[i]);
}

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
            for(int col = i + 1; col < m->size; col++)
                m->data[row][col] -= m->data[i][col] * multiplier;
            m->sol[row] -= m->sol[i] * multiplier;
        }
    }
}
