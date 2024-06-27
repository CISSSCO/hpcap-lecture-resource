#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 1000000
#define T 16

int arr[N];
pthread_barrier_t barrier;

void *hello(void* threadId) {
    long tid = (long)threadId;
    long *localSum = malloc(sizeof(long)); // Allocate memory for the local sum
    *localSum = 0;
    int chunk_size = N / T;
    int start = tid * chunk_size;
    int end = (tid + 1) * chunk_size;

    // Ensure the last thread processes the remaining elements
    if (tid == T - 1) {
        end = N;
    }

    // Initialize the chunk of the array
    if(tid == 0){
        for (int i = 0; i < N; i++) {
                arr[i] = i + 1;
        }
    }

    // Wait for all threads to finish initialization
    pthread_barrier_wait(&barrier);

    // Compute the local sum
    for (int i = start; i < end; i++) {
        *localSum += arr[i];
    }

    return (void*)localSum;
}

int main() {
    pthread_t threads[T];
    void *status;
    long sum = 0;

    // Initialize the barrier
    pthread_barrier_init(&barrier, NULL, T);

    // Create threads
    for (long i = 0; i < T; i++) {
        pthread_create(&threads[i], NULL, hello, (void*)i);
    }

    // Join threads and aggregate the local sums
    for (long i = 0; i < T; i++) {
        pthread_join(threads[i], &status);
        sum += *(long*)status;
        free(status); // Free the allocated memory for the local sum
    }

    // Destroy the barrier
    pthread_barrier_destroy(&barrier);

    printf("Sum using manual reduction: %ld\n", sum);
    printf("Natural Number sum original: %ld\n", ((N * 1L * (N + 1)) / 2));

    return 0;
}
