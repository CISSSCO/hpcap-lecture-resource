#include<omp.h>
#include<stdio.h>
#define N 100
int main(){
    omp_set_num_threads(5);
    int suma = 0;
    int sumb = 0;
    int i = 1;
    #pragma omp parallel firstprivate(i)
    {
        #pragma omp sections reduction(+: suma) reduction(+: sumb)
        {
            #pragma omp section
            for( ; i <= N; i++){
                suma+= i;
            }
            printf("Sum by section 1 = %d\n", suma);
            #pragma omp section
            for( ; i <= N; i++){
                sumb+= i;
            }
            printf("Sum by section 2 = %d\n", sumb);
        }
    }
}
