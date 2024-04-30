#include<stdio.h>
#include<omp.h>
int main(){
    int tid = 0;
    int totalThread = 0;
    omp_set_num_threads(10);
    #pragma omp parallel 
    {
        tid = omp_get_thread_num();
        totalThread = omp_get_num_threads();
        printf("Hello from thread %d of %d\n", tid, totalThread);

    }
    return 0;
}
