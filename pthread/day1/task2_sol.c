#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define N 16
int arr[N];
void* hello(void* threadId){
    long tid = (long)threadId;
    sleep(100);
    printf("Thread id %ld is printing %d\n", tid, arr[tid]);
    printf("Joining\n");
    return NULL;
}
int main(){
    pthread_t t[N];
    for(int i = 0; i < N; i++){
        arr[i] = i;
    }
    for(long i = 0; i < N; i++){
        pthread_create(&t[i], NULL, hello, (void*) i);
    }
    /*
    for(long i = 0; i < N; i++){
        pthread_join(t[i], NULL);
    }*/
    return 0;
}
