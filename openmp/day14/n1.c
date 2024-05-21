#include<stdio.h>
#include<omp.h>
int main(){
    omp_set_nested(1);
    //omp_set_dynamic(1);
    #pragma omp parallel num_threads(4)
    {
        int t1 = omp_get_thread_num();
        #pragma omp parallel num_threads(4)
        {
            int t2 = omp_get_thread_num();
            printf("hello from %d inside %d\n", t2, t1);
        }
    }
}
