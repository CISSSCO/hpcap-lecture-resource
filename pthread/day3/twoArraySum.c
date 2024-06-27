#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 10000
#define T 20

int *arr1;
int *arr2;
int *arr3;

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
        arr3[i] = arr1[i] + arr2[i];
    }

    return NULL;
}

int main() {
    arr1 = (int*)malloc(sizeof(int) * N);
    arr2 = (int*)malloc(sizeof(int) * N);
    arr3 = (int*)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        arr1[i] = i + 1;
        arr2[i] = i + 1;
        arr3[i] = 0;
    }

    pthread_t threads[T];

    // Create threads
    for (long i = 0; i < T; i++) {
        pthread_create(&threads[i], NULL, hello, (void*)i);
    }

    // Join threads and aggregate the local sums
    for (long i = 0; i < T; i++) {
        pthread_join(threads[i], NULL);
    }

    for(int i = 0; i < N; i++){
        printf("%d ",arr3[i]);
    }

    return 0;
}
