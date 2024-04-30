#include<stdio.h>
#include<omp.h>
int main(){
    int tid = 0;
    int totalThread = 0;
    #pragma omp parallel 
    {
        printf("Hello from thread %d of %d\n", tid, totalThread);

    }
    return 0;
}
