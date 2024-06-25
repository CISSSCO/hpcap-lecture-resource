#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define N 2
void *hello(void* threadId){
    long tid = (long)threadId;
    printf("Hello World %ld of %d\n", tid, N);
    return NULL;
}
int main(){
    pthread_t t1, t2;

    pthread_create(&t1, NULL, hello, (void*) 0);
    pthread_join(t1, NULL);
    pthread_create(&t2, NULL, hello, (void*) 1);
    pthread_join(t2, NULL);
    return 0;
}
