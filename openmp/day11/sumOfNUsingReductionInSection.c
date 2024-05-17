#include<omp.h>
#include<stdio.h>
#define N 10
int main(){
    omp_set_num_threads(5);
    int suma = 0;
    int i = 1;
    int prodb = 1;
    #pragma omp parallel firstprivate(i) firstprivate(prodb)
    {
        #pragma omp sections reduction(+: suma) 
        {
            #pragma omp section
            {
                for(i = 1 ; i <= N; i++){
                    suma+= i;
                }
                printf("Sum by section 1 = %d\n", suma);
            }
            #pragma omp section
            {
                for(i = 1 ; i <= N; i++){
                    prodb*= i;
                }
                printf("Product by section 2 = %d\n", prodb);
            }
        }
    }
}
