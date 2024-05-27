#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000

void sum(int* arr, int start, int end, int* result) {
    printf("task executed by %d\n", omp_get_thread_num());
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += arr[i];
    }
    *result = sum;
}

int main() {
    int* arr = (int*) malloc(N * sizeof(int));
    int result1 = 0, result2 = 0, total = 0;

    // Initialize the array
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    #pragma omp parallel num_threads(5)
    {
        #pragma omp single
        {
            printf("task created by %d\n", omp_get_thread_num());
            #pragma omp task
            sum(arr, 0, N/2, &result1);
            
            #pragma omp task
            sum(arr, N/2, N, &result2);

            #pragma omp taskwait
        }
    }

    total = result1 + result2;
    printf("Total sum: %d\n", total);

    free(arr);
    return 0;
}

