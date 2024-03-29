#ifndef __MATRIX_H
#define __MATRIX_H

struct t_matrix {
    double **data;
    int size;
};

struct t_matrix* create_matrix(int size);

void delete_matrix(struct t_matrix* m);

void read_input(struct t_matrix* m);

void print_matrix(struct t_matrix* m);

void print_solution(struct t_matrix *m, struct t_matrix *original_matrix);

void gaussian_elim(struct t_matrix* m);

void gauss_seidel(struct t_matrix* m);

void gaussian_elim_trid(struct t_matrix* m);

void gauss_seidel_trid(struct t_matrix* m);

#endif
