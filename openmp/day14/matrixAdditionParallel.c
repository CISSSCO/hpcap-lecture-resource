#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100000

int main() {
    int **a, **b, **c, **cp;
    double start_time, end_time, serial_time, parallel_time;

    // Dynamic memory allocation
    a = (int**) malloc(sizeof(int*) * N);
    b = (int**) malloc(sizeof(int*) * N);
    c = (int**) malloc(sizeof(int*) * N);
    cp = (int**) malloc(sizeof(int*) * N);
    for (int i = 0; i < N; i++) {
        a[i] = (int*) malloc(sizeof(int) * N);
        b[i] = (int*) malloc(sizeof(int) * N);
        c[i] = (int*) malloc(sizeof(int) * N);
        cp[i] = (int*) malloc(sizeof(int) * N);
    }

    // Initialization of data
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = rand() % 100 + 1;
            b[i][j] = rand() % 100 + 1;
            c[i][j] = 0;
            cp[i][j] = 0;
        }
    }

    // Serial matrix addition
    start_time = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    end_time = omp_get_wtime();
    serial_time = end_time - start_time;

    // Parallel matrix addition using OpenMP
    start_time = omp_get_wtime();
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cp[i][j] = a[i][j] + b[i][j];
        }
    }
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;

    // Print the time taken for serial and parallel additions
    printf("Time taken for serial addition: %f seconds\n", serial_time);
    printf("Time taken for parallel addition: %f seconds\n", parallel_time);

    // Validate the results
    int flag = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (c[i][j] != cp[i][j]) {
                flag = 0;
                break;
            }
        }
    }

    if (flag) {
        printf("_____Passed_____\n");
    } else {
        printf("_____Failed_____\n");
    }

    // Freeing allocated memory
    for (int i = 0; i < N; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
        free(cp[i]);
    }
    free(a);
    free(b);
    free(c);
    free(cp);

    return 0;
}

