#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define N 1000
int main(){
    int arr[N];
    for(int i = 0; i < N; i++){
        arr[i] = rand() % 1000;
    }
    int serialSum = 0;
    for(int i = 0; i < N; i++){
        serialSum += arr[i];
    }

    int parallelSum = 0;
    #pragma omp parallel for
    for(int i = 0; i < N; i++){
        #pragma omp atomic update
        parallelSum+= arr[i];
    }
    printf("SerialSum = %d\n", serialSum);
    printf("ParallelSum = %d\n", parallelSum);
    return 0;
}
