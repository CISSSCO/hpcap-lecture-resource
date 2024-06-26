#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define N 100000

long sum = 0;
void *hello(void* threadId){
    long tid = (long)threadId;
    sum += (tid);
    return NULL;
}

int main(){
    pthread_t* t;
    t = malloc(sizeof(pthread_t) * N);

    for(long i = 0; i < N; i++)
        pthread_create(&t[i], NULL, hello, (void*)i);
    for(long i = 0; i < N; i++)
        pthread_join(t[i], NULL);
    printf("Natural Number sum: %ld\n", sum + N);
    printf("Expected Natural Number sum: %ld\n", (N * (N + 1) / 2));
    free(t);
    return 0;
}
