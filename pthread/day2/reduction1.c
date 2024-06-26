#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define N 5000000
#define T 16

pthread_mutex_t mutex;
long sum = 0;
int arr[N];

void *hello(void* threadId){
    long tid = (long)threadId;
    long localSum = 0;
    int chunk_size = N / T;
    int start = tid * chunk_size;
    int end = (tid + 1) * chunk_size;
    if (tid == T - 1) {
        end = N;
    }
    for (int i = start; i < end; i++) {
        localSum += (long)arr[i];
    }
    pthread_mutex_lock(&mutex);
    sum += localSum;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(){
    for(int i = 0; i < N; i++){
        arr[i] = i + 1;
    }
    pthread_t* t;
    pthread_mutex_init(&mutex, NULL);
    t = malloc(sizeof(pthread_t) * N);

    for(long i = 0; i < T; i++)
        pthread_create(&t[i], NULL, hello, (void*)i);
    for(long i = 0; i < T; i++)
        pthread_join(t[i], NULL);
    pthread_mutex_destroy(&mutex);
    printf("Sum using manual reduction: %ld\n", sum);
    printf("Natural Number sum original: %ld\n", ((N * ((N + 1) * 1L)) / 2));
    free(t);
    return 0;
}
