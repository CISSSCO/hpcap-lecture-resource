#include<stdio.h>
#include<omp.h>
#define N 100

int main(){
    int a[N];
    int maxi = 0;

    #pragma omp parallel num_threads(N)
    {
        int i = omp_get_thread_num();
        a[i] = i + 1;

        #pragma omp barrier

        #pragma omp master 
        for(int j = 0; j < N; j++){
            if(a[j] > maxi) maxi = a[j];
        }
    }
    printf("Max number = %d\n", maxi);
    return 0;
}
