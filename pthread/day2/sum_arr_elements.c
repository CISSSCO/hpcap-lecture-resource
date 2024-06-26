#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define N 300000

pthread_mutex_t mutex;
long sum = 0;
int arr[N];
void *hello(void* threadId){
    long tid = (long)threadId;
    pthread_mutex_lock(&mutex);
    sum += arr[tid];
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

    for(long i = 0; i < N; i++)
        pthread_create(&t[i], NULL, hello, (void*)i);
    for(long i = 0; i < N; i++)
        pthread_join(t[i], NULL);
    pthread_mutex_destroy(&mutex);
    printf("Natural Number sum: %ld\n", sum);
    printf("Natural Number sum original: %ld\n", ((N * ((N + 1) * 1L)) / 2));
    free(t);
    return 0;
}
