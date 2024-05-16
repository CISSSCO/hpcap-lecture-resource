#include<omp.h>
#include<stdio.h>
#define N 10


int main(){
    omp_set_num_threads(12);
    int i;
    int a[N], b[N], c[N], d[N], e[N];

    for(i = 0; i < N; i++){
        a[i] = i * 2;
        b[i] = i + 2;
        e[i] = a[i] + b[i];
    }

    #pragma omp parallel default(none) shared(a, b, c, d, e) private(i)
    {
        #pragma omp sections 
        {
            #pragma omp section
            for(i = 0; i < N; i++){
                c[i] = a[i] + b[i];
                printf("section 1 # working thread: %d\t| %d + %d = %d\n", omp_get_thread_num(), a[i], b[i], c[i]);
            }
            #pragma omp section
            for(i = 0; i < N; i++){
                d[i] = a[i] * b[i];
                printf("section 2 # working thread: %d\t| %d * %d = %d\n", omp_get_thread_num(), a[i], b[i], d[i]);
            }
            #pragma omp section
            for(i = 0; i < N; i++){
                e[i] = a[i] / b[i];
                printf("section 3 # working thread: %d\t| %d / %d = %d\n", omp_get_thread_num(), a[i], b[i], e[i]);
            }
        }

    }
}
