#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mtrxlib.h"

struct t_matrix* create_matrix(int size) {
    int i;
    struct t_matrix* m;

    if(! (m = malloc(sizeof(struct t_matrix)))) {
        fprintf(stderr, "Erro ao alocar memória");
        return NULL;
    }

    m->size = size;
    if(! (m->data = calloc(m->size, sizeof(double*)))) {
        fprintf(stderr, "Erro ao alocar memória");
        return NULL;
    }

    for (i = 0; i < m->size; i++)
        /*
         * Alocado em cada linha uma coluna a mais para já guardar dentro da
         * estrutura a solução do sistema.
         */
        if(! (m->data[i] = calloc(m->size + 1, sizeof(double)))) {
            fprintf(stderr, "Erro ao alocar memória");
            return NULL;
        }

    return m;
}

void delete_matrix(struct t_matrix* m) {
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

void read_input(struct t_matrix* matrix) {
    int i, j;

    for(i = 0; i < matrix->size; i++)
        for(j = 0; j <= matrix->size; j++)
            scanf("%lf", &matrix->data[i][j]);
}

/*
 * Função auxiliar para formatar a saída do sistema
 */
void find_max_column_widths(struct t_matrix* m, int *widths) {
    int i, j;

    for (j = 0; j < m->size+1; j++) {
        int max_width = 0;

        for (i = 0; i < m->size; i++) {
            int current_width = snprintf(NULL, 0, "%.5lf", m->data[i][j]);

            if (max_width < current_width) {
                max_width = current_width;
            }
        }
        widths[j] = max_width;
    }
}

/*
 * Função para debugging. Imprime o sistema linear na saída padrão.
 */
void print_matrix(struct t_matrix* m) {
    int i, j;
    int column_widths[m->size + 1];
    find_max_column_widths(m, column_widths);

    for (i = 0; i < m->size; i++) {
        for (j = 0; j < m->size; j++)
            printf("%*.5lf   ", column_widths[j], m->data[i][j]);
        printf("%*.5lf\n", column_widths[j], m->data[i][j]);
    }
}

void print_solution(struct t_matrix *m, struct t_matrix *original_matrix) {
    int i, j;
    double solution[m->size];
    double residual[m->size];

    for(i = m->size - 1; i >= 0; i--) {
        solution[i] = m->data[i][m->size];
        for(j = i + 1; j < m->size; j++)
            solution[i] -= m->data[i][j] * solution[j];
        solution[i] /= m->data[i][i];
    }
    for(i = 0; i < m->size; i++) {
        residual[i] = (-1) * original_matrix->data[i][m->size];
        for(j = 0; j < original_matrix->size; j++)
            residual[i] += original_matrix->data[i][j] * solution[j];
    }

    printf("X = [");
    for(i = 0; i < m->size - 1; i++)
        printf("%.12f   ", solution[i]);
    printf("%.12f]\n", solution[i]);
    printf("R = [");
    for(i = 0; i < m->size - 1; i++)
        printf("%.8e   ", residual[i]);
    printf("%.8e]\n", residual[i]);
}

void swap_lines(struct t_matrix* m, int a, int b) {
    double* aux_pointer = m->data[a];
    m->data[a] = m->data[b];
    m->data[b] = aux_pointer;
}

int get_max_column_value(struct t_matrix* m, int column) {
    int candidate = column;

    for(int j = column + 1; j < m->size; j++)
        if(fabs(m->data[candidate][column]) < m->data[j][column])
            candidate = j;

    return candidate;
}

void pivoting(struct t_matrix* m, int i) {
    int pivot_candidate = get_max_column_value(m, i);

    if(pivot_candidate != i)
        swap_lines(m, i, pivot_candidate);
}

void gaussian_elim(struct t_matrix* m) {
    for(int i = 0; i < m->size; i++) {
        pivoting(m, i);

        for(int row = i + 1; row < m->size; row++) {
            double multiplier = m->data[row][i] / m->data[i][i];

            m->data[row][i] = 0.0;
            for(int col = i + 1; col <= m->size; col++)
                m->data[row][col] -= m->data[i][col] * multiplier;
        }
    }
}
