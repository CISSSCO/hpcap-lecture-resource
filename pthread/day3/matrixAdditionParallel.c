#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 400
#define T 4

int **m1, **m2, **sumMat;
pthread_mutex_t mutex;
int data_ready = 0;

void *matrixAddition(void* threadId) {
    long tid = (long)threadId;
    int chunk_size = N / T;
    int start = tid * chunk_size;
    int end = (tid + 1) * chunk_size;

    for (int i = start; i < end; i++) {
        for (int j = start; j < end; j++) {
            sumMat[i][j] = m1[i][j] + m2[i][j];
        }
    }

    return NULL;
}

int main(int argc, char **argv) {
    pthread_t threads[T];
    pthread_mutex_init(&mutex, NULL);

    m1 = (int**)malloc(sizeof(int*) * N);
    m2 = (int**)malloc(sizeof(int*) * N);
    sumMat = (int**)malloc(sizeof(int*) * N);
    for (int i = 0; i < N; i++) {
        m1[i] = (int*)malloc(sizeof(int) * N);
        m2[i] = (int*)malloc(sizeof(int) * N);
        sumMat[i] = (int*)malloc(sizeof(int) * N);
    }

        for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                m1[i][j] = 1;
                m2[i][j] = 1;
                }
        }
    // Create threads for initialization and summing
    for (long i = 0; i < T; i++) {
        pthread_create(&threads[i], NULL, matrixAddition, (void*)i);
    }

    // Join threads
    for (long i = 0; i < T; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    // Print result matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", sumMat[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    for (int i = 0; i < N; i++) {
        free(m1[i]);
        free(m2[i]);
        free(sumMat[i]);
    }
    free(m1);
    free(m2);
    free(sumMat);

    return 0;
}
