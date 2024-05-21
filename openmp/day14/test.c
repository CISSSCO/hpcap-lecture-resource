#include<stdio.h>
#include<omp.h>
int main(){
    omp_set_nested(1);
    #pragma omp parallel num_threads(3) 
    {
        int tid1 = omp_get_thread_num();
        #pragma omp parallel num_threads(3) if(omp_get_nested())
        {
            int tid2 = omp_get_thread_num();
            printf("Hello from %d inside %d\n", tid2, tid1);
        }
    }

    return 0;
}
