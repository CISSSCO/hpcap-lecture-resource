#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000

void sum(int* arr, int start, int end, int* result) {
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += arr[i];
    }
    *result = sum;
}

void totalSum(int* result1, int* result2, int* total) {
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
        #pragma omp single
        {
            #pragma omp task 
            sum(arr, 0, N/2, &result1);
            
            #pragma omp task 
            sum(arr, N/2, N, &result2);

            #pragma omp taskwait

            #pragma omp task 
            totalSum(&result1, &result2, &total);
        }

    }

    printf("Total sum: %d\n", total);

    free(arr);
    return 0;
}

