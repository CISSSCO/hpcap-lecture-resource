#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 3000000
#define T 16

int arr[N];
pthread_mutex_t mutex;
pthread_cond_t cond;
int data_ready = 0; // Condition to indicate if the data is ready

void *initialize_and_sum(void* threadId) {
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

    if (tid == 0) {
        // Thread 0 initializes the array
        for (int i = 0; i < N; i++) {
            arr[i] = i + 1;
        }

        // Signal all other threads that data is ready
        pthread_mutex_lock(&mutex);
        data_ready = 1;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    } else {
        // Other threads wait until the data is initialized
        pthread_mutex_lock(&mutex);
        while (data_ready != 1) {
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);
    }

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

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // Create threads for initialization and summing
    for (long i = 0; i < T; i++) {
        pthread_create(&threads[i], NULL, initialize_and_sum, (void*)i);
    }

    // Join threads and aggregate the local sums
    for (long i = 0; i < T; i++) {
        pthread_join(threads[i], &status);
        sum += *(long*)status;
        free(status); // Free the allocated memory for the local sum
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    printf("Sum using manual reduction: %ld\n", sum);
    printf("Natural Number sum original: %ld\n", ((N * 1L * (N + 1)) / 2));

    return 0;
}
