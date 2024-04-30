#include<stdio.h>
#ifdef _OPENMP
#include<omp.h>
#endif
int main(){
    int tid = 0;
    int totalThread = 0;
#ifdef _OPENMP
    omp_set_num_threads(10);
#endif
    #pragma omp parallel 
    {
#ifdef _OPENMP
        tid = omp_get_thread_num();
        totalThread = omp_get_num_threads();
#endif
        printf("Hello from thread %d of %d\n", tid, totalThread);

    }
    return 0;
}
