#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 2000

int main() {
    int *a, *b, *c, *cp;
    double start_time, end_time, serial_time, parallel_time;

    // Dynamic memory allocation
    a = (int*) malloc(sizeof(int) * N * N);
    b = (int*) malloc(sizeof(int) * N * N);
    c = (int*) malloc(sizeof(int) * N * N);
    cp = (int*) malloc(sizeof(int) * N * N);

    // Initialization of data
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i * N + j] = rand() % 100 + 1;
            b[i * N + j] = rand() % 100 + 1;
            c[i * N + j] = 0;
            cp[i * N + j] = 0;
        }
    }

    // Serial matrix multiplication
    start_time = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += a[i * N + k] * b[k * N + j];
            }
            c[i * N + j] = sum;
        }
    }
    end_time = omp_get_wtime();
    serial_time = end_time - start_time;

    // Parallel matrix multiplication using OpenMP
    start_time = omp_get_wtime();
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += a[i * N + k] * b[k * N + j];
            }
            cp[i * N + j] = sum;
        }
    }
    end_time = omp_get_wtime();
    parallel_time = end_time - start_time;

    // Print the time taken for serial and parallel multiplications
    printf("Time taken for serial multiplication: %f seconds\n", serial_time);
    printf("Time taken for parallel multiplication: %f seconds\n", parallel_time);

    // Validate the results
    int flag = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (c[i * N + j] != cp[i * N + j]) {
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
    free(a);
    free(b);
    free(c);
    free(cp);

    return 0;
}

