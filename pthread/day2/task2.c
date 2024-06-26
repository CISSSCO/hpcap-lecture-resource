#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define N 20

int arr[N];
void *hello(void* threadId){
    long tid = (long)threadId;
    arr[tid] = tid;
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
    for(int i = 0; i < N; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}
