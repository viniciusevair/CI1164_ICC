void gaussianElim(struct tMatrix* m);

void gaussianElimTrid(double *d, double *a, double *c, double *b,
                      double *x, unsigned int n);

void getSolution(struct tMatrix *m, double *x);

void getTridSolution(struct tTridMatrix *m, double *x);
