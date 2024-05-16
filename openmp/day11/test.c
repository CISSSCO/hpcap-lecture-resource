#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#define N 990084


int main(){
    omp_set_num_threads(5);
    int a[N], b[N];
    int i;

    #pragma omp parallel shared(a, b, i) 
    {
        for(i = 0 ; i < N; i++){
            #pragma omp sections
            {
                #pragma omp section
                a[i] = i;
                #pragma omp section
                b[i] = i;
                
            }
        }
        #pragma omp master
        for(int i = 0; i < N; i++){
            if(a[i] == b[i]) continue;
            else{
                printf("both array not equal\n");
                exit(0);
            }
        }

    }
    printf("both array equal\n");
}
