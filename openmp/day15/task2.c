#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000

void task_compute(int* arr, int start, int end, int* result) {
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += arr[i];
    }
    *result = sum;
}

void task_finalize(int* result1, int* result2, int* total) {
    *total = *result1 + *result2;
}

int main() {
    int* arr = (int*) malloc(N * sizeof(int));
    int result1 = 0, result2 = 0, total = 0;

    // Initialize the array
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    #pragma omp parallel
    {
        #pragma omp task depend(out: result1)
        task_compute(arr, 0, N/2, &result1);
        
        #pragma omp task depend(out: result2)
        task_compute(arr, N/2, N, &result2);

        #pragma omp task depend(in: result1, result2) depend(out: total)
        task_finalize(&result1, &result2, &total);

        #pragma omp taskwait
    }

    printf("Total sum: %d\n", total);

    free(arr);
    return 0;
}

