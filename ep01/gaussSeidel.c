#include "linSys.h"
#include <math.h>
#include <string.h>

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
        //calcula erro entre x e lastIteration
        if(it > 0)
            err = getMaxDiff(x, lastIteration, n);
        //troca x e lastIteration
        memcpy(lastIteration, x, sizeof(double) * n);
        it++;
    }
    deleteArray(lastIteration);
    return it;
}

