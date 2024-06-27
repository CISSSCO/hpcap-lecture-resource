#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 1000000
#define T 20

int arr[N];

void *hello(void* threadId) {
    long tid = (long)threadId;
    long localSum = 0; // Changed to long to match sum type
    int chunk_size = N / T;
    int start = tid * chunk_size;
    int end = (tid + 1) * chunk_size;

    // Ensure the last thread processes the remaining elements
    if (tid == T - 1) {
        end = N;
    }

    for (int i = start; i < end; i++) {
        localSum += arr[i];
    }

    pthread_exit((void*) localSum);
}

int main() {
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    pthread_t threads[T];
    void *status;
    long sum = 0; // Changed to long to match localSum type

    // Create threads
    for (long i = 0; i < T; i++) {
        pthread_create(&threads[i], NULL, hello, (void*)i);
    }

    // Join threads and aggregate the local sums
    for (long i = 0; i < T; i++) {
        pthread_join(threads[i], &status);
        sum += (long)status;
    }

    printf("Sum using manual reduction: %ld\n", sum);
    printf("Natural Number sum original: %ld\n", ((N * 1L * (N + 1)) / 2));

    return 0;
}
