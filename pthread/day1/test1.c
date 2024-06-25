#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#define N 2
void* hello(void* threadId){
    long tid = (long)threadId;
    printf("Forking %ld of %d\n", tid, N);
    sleep(1);
    printf("Joining %ld of %d\n", tid, N);
    return NULL;
}
int main(){
    pthread_t t1, t2, t3, t4;
    pthread_create(&t1, NULL, hello, (void*) 0);
    pthread_create(&t2, NULL, hello, (void*) 1);
    pthread_create(&t3, NULL, hello, (void*) 2);
    pthread_create(&t4, NULL, hello, (void*) 3);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    return 0;
}
