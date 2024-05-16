#include<omp.h>
#include<stdio.h>
#define N 10


int main(){
    omp_set_num_threads(5);
    int i;
    int a[N], b[N], c[N], d[N];

    for(i = 0; i < N; i++){
        a[i] = i * 2;
        b[i] = i + 2;
    }

    i = 0;
    //printf("%d\n", i);
    #pragma omp parallel shared(a, b, c, d, i) lastprivate(i)
    {
        #pragma omp sections 
        {
            //printf("%d\n", i);
            #pragma omp section
            for( ; i < N; i++){
                c[i] = a[i] + b[i];
                printf("section 1 # working thread: %d\t| %d + %d = %d\n", omp_get_thread_num(), a[i], b[i], c[i]);
            }
            #pragma omp section
            for( ; i < N; i++){
                d[i] = a[i] * b[i];
                printf("section 2 # working thread: %d\t| %d * %d = %d\n", omp_get_thread_num(), a[i], b[i], d[i]);
            }
        }

    }
    //printf("%d\n", i);
}
