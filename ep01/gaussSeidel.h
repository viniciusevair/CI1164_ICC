/* Autores: Luiz Henrique Murback Wiedmer GRR20221234, Vinicius Evair da Silva GRR20221251. */ 

int gaussSeidel(struct tMatrix *m, double *x, double tol);

int gaussSeidelTrid(double *d, double *a, double *c, double *b,
                    double *x, unsigned int n, double tol);
