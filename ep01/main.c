#include <stdio.h>
#include <string.h>
#include "mtrxlib.h"

int main(int argc, char *argv[]) {
    int matrix_size;
    struct t_matrix *m, *n;
    scanf("%d", &matrix_size);
    printf("The size will be %d\n", matrix_size);

    m = create_matrix(matrix_size);
    n = create_matrix(matrix_size);
    printf("Allocated space for all the matrix!\n");
    printf("I'll now read the data.\n");
    read_input(m);
    for(int i = 0; i < matrix_size; i++)
        memcpy(n->data[i], m->data[i], (matrix_size + 1)*sizeof(double));

    print_matrix(m);
    printf("TESTTESTETSTSTETESTSETESTESTES:\n");
    print_matrix(n);
    printf("------------\n");
    gaussian_elim(n);
    print_matrix(n);
    print_solution(n, m);

    delete_matrix(m);

    return 0;
}
