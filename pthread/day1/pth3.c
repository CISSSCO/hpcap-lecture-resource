#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define N 10

void *hello(void* threadId){
    long tid = (long)threadId;

    printf("Hello World %ld of %d\n", tid, N);
    return NULL;
}

int main(){
    pthread_t* t;
    t = malloc(sizeof(pthread_t) * N);

    for(long i = 0; i < N; i++)
        pthread_create(&t[i], NULL, hello, (void*)i);
    for(long i = 0; i < N; i++)
        pthread_join(t[i], NULL);
    free(t);
    return 0;
}
