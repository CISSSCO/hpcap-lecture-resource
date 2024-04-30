#include<stdio.h>
#include<omp.h>
#define N 100
int main(){
    int a[N];
    int sum = 0;
    #pragma omp parallel num_threads(N)
    {
        int i = omp_get_thread_num();
        a[i] = i + 1;
        #pragma omp barrier
        if(omp_get_thread_num() == 0){
            for(int j = 0; j < N; j++){
                sum+= a[j];
            }
        }
    }
    printf("Sum = %d\n", sum);
    return 0;
}
