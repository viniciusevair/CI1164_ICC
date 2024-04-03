int gaussSeidel(struct tMatrix *m, double *b, double *x, double tol);

int gaussSeidelTrid(double *d, double *a, double *c, double *b,
                    double *x, unsigned int n, double tol);
